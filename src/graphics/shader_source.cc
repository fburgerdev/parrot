#include "common.hh"
#include "shader_source.hh"

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

  // (constructor)
  ShaderSource::ShaderSource(const AssetPath& asset_path, AssetAPI& asset_api)
    : ShaderSource((ostrstream() << ifstream(asset_path.filepath).rdbuf()).str()) {}
  ShaderSource::ShaderSource(const string& source) {
    usize offset = 0;
    Opt<Variant<ShaderStage, Snippet>> current;
    while (true) {
      usize open_index = source.find("[[", offset);
      usize close_index = source.find("]]", offset);
      if (open_index == string::npos || close_index == string::npos) {
        break;
      }
      string inner = source.substr((open_index + 2), close_index - (open_index + 2));
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
              snippet.body.emplace_back(SnippetInclude({ identifier, (splitted.back() == "optional") }));
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
            if (std::holds_alternative<ShaderStage>(*current)) {
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
}