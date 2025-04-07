#include "common.hh"
#include "shader_source.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (static) split
  static List<string> split(strview str, const List<char>& delim) {
    List<string> out = { "" };
    for (char ch : str) {
      if (std::find(delim.begin(), delim.end(), ch) != delim.end()) {
        if (!out.back().empty()) {
          out.emplace_back();
        }
      }
      else {
        out.back().push_back(ch);
      }
    }
    if (out.back().empty()) {
      out.pop_back();
    }
    return out;
  }
  // (static) join
  static string join(strview delim, auto begin, auto end) {
    string out;
    for (auto it = begin; it != end; ++it) {
      out += *it;
      if (std::next(it) != end) {
        out += delim;
      }
    }
    return out;
  }

  //* ShaderSource
  // (constructor)
  ShaderSource::ShaderSource(const string& source) {
    usize offset = 0;
    Opt<Variant<ShaderStage, Snippet>> current;
    while (true) {
      usize open_index = source.find("[[", offset);
      usize close_index = source.find("]]", offset);
      if (open_index == string::npos || close_index == string::npos) {
        break;
      }
      string inner = source.substr(
        (open_index + 2), close_index - (open_index + 2)
      );
      List<string> splitted = split(inner, { ' ', '(', ')', '"' });
      if (splitted.size()) {
        if (splitted.front() == "vertex" || splitted.front() == "fragment") {
          string version = join(" ", splitted.begin() + 1, splitted.end());
          if (splitted.front() == "vertex") {
            current = ShaderStage({
              .type = ShaderStage::Type::VERTEX,
              .version = version
            });
          }
          else if (splitted.front() == "fragment") {
            current = ShaderStage({
              .type = ShaderStage::Type::FRAGMENT,
              .version = version
            });
          }
        }
        else if (splitted.front() == "snippet") {
          current = Snippet({ .name = splitted.at(1) });
        }
        else if (splitted.front() == "include") {
          string identifier = splitted.at(1);
          if (current) {
            std::visit([&](Snippet& snippet) {
              snippet.name = identifier;
              snippet.body.emplace_back(
                source.substr(offset, open_index - offset)
              );
              snippet.body.emplace_back(
                SnippetInclude({ identifier, (splitted.back() == "optional") })
              );
            }, * current);
          }
        }
        else if (splitted.front() == "end") {
          if (current) {
            std::visit([&](Snippet& snippet) {
              snippet.body.emplace_back(
                source.substr(offset, open_index - offset)
              );
            }, * current);
            if (holds<ShaderStage>(*current)) {
              ShaderStage& stage = std::get<ShaderStage>(*current);
              if (stage.type == ShaderStage::Type::VERTEX) {
                vertex = std::move(stage);
              }
              else if (stage.type == ShaderStage::Type::FRAGMENT) {
                fragment = std::move(stage);
              }
            }
            else {
              Snippet& snippet = std::get<Snippet>(*current);
              snippets.emplace(snippet.name, std::move(snippet));
            }
          }
          current = std::nullopt;
        }
      }
      offset = close_index + 2;
    }
  }
  // :: for Asset
  ShaderSource::ShaderSource(const AssetPath& path, AssetAPI& api)
    : ShaderSource((ostrstream() << ifstream(path.file).rdbuf()).str()) {}
  ShaderSource::ShaderSource(
    const SerialNode&, const AssetPath& path, AssetAPI&
  ) : Asset(path) {
    LOG_ASSET_ERROR("this method only exists to implement the asset-api");
  }

  // toString
  string ShaderSource::Snippet::toString() const {
    string out;
    for (const auto& part : body) {
      if (holds<SnippetInclude>(part)) {
        const SnippetInclude& include = std::get<SnippetInclude>(part);
        if (include.is_optional) {
          out += "[[include \"" + include.identifier + "\" optional]]";
        }
        else {
          out += "[[include \"" + include.identifier + "\"]]";
        }
      }
      else {
        out += std::get<string>(part);
      }
    }
    return out;
  }
  string ShaderSource::ShaderStage::toString() const {
    return "#version " + version + Snippet::toString();
  }

  //* ShaderProgram
  // (constructor) for Asset
  ShaderProgram::ShaderProgram(const AssetPath& path, AssetAPI& api) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  ShaderProgram::ShaderProgram(
    const SerialNode& node, const AssetPath& path, AssetAPI& api
  ) : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void ShaderProgram::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    _sources.emplace_back(
      AssetPath(stdf::path(".parrot/model.glsl.macro")), api
    );
    _sources.emplace_back(
      AssetPath(stdf::path(".parrot/surface.glsl.macro")), api
    );
    if (node.contains("sources")) {
      for (const auto& source_node : node.at("sources")) {
        _sources.emplace_back(
          AssetPath(stdf::path(string(source_node))), api
        );
      }
    }
  }

  // resolveShaderStages
  Pair<string, string> ShaderProgram::resolveShaderStages() const {
    // lock
    List<SharedPtr<const ShaderSource>> locked_sources;
    for (const auto& source : _sources) {
      locked_sources.emplace_back(source.lock());
    }
    // merge
    ShaderSource::ShaderStage vertex;
    ShaderSource::ShaderStage fragment;
    Map<string, ShaderSource::Snippet> snippets;
    for (auto& locked_source : locked_sources) {
      if (locked_source->vertex) {
        vertex = locked_source->vertex.value();
      }
      if (locked_source->fragment) {
        fragment = locked_source->fragment.value();
      }
      for (const auto& [name, snippet] : locked_source->snippets) {
        snippets.emplace(name, snippet);
      }
    }
    // resolve
    Set<ShaderSource::Snippet*> resolved;
    Func<void(ShaderSource::Snippet&)> resolve = [&](
      ShaderSource::Snippet& snippet
      ) {
        if (resolved.contains(&snippet)) {
          return;
        }
        for (auto& part : snippet.body) {
          if (holds<ShaderSource::SnippetInclude>(part)) {
            auto& include = std::get<ShaderSource::SnippetInclude>(part);
            if (snippets.contains(include.identifier)) {
              resolve(snippets.at(include.identifier));
              part = snippets.at(include.identifier).toString();
            }
            else {
              if (include.is_optional) {
                part = string();
              }
              else {
                // TODO: error
              }
            }
          }
        }
        resolved.insert(&snippet);
      };
    resolve(vertex);
    resolve(fragment);

    return {
      vertex.toString(),
      fragment.toString()
    };
  }
}