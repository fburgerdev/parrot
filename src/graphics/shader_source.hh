#pragma once
#include "core/asset_handle.hh"
#include "core/log.hh"

namespace Parrot {
  // ShaderSource
  class ShaderSource : public Asset {
  public:
    // (constructor)
    ShaderSource(const string& source);
    // :: for Asset
    ShaderSource(const AssetPath& path, AssetAPI& api);
    ShaderSource(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      LOG_ASSET_ERROR("this method only exists to implement the asset-api");
    }

    // SnippetInclude
    struct SnippetInclude {
      // identifier, is_optional
      string identifier;
      bool is_optional = false;
    };
    // Snippet
    struct Snippet {
      // toString
      string toString() const {
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

      // name, body
      string name;
      List<Variant<SnippetInclude, string>> body;
    };
    // ShaderStage
    struct ShaderStage : public Snippet {
      // Type
      enum class Type {
        NONE = 0, VERTEX, FRAGMENT
      };

      // toString
      string toString() const {
        return "#version " + version + Snippet::toString();
      }

      // type, version
      Type type = Type::NONE;
      string version = "330 core";
    };

    // vertex, fragment, snippets
    Opt<ShaderStage> vertex, fragment;
    Map<string, Snippet> snippets;
  };

  // ShaderProgram
  class ShaderProgram : public Asset {
  public:
    // (constructor) for Asset
    ShaderProgram(const AssetPath& path, AssetAPI& api);
    ShaderProgram(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
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
    Pair<string, string> resolveShaderStages() const {
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
  private:
    List<AssetHandle<ShaderSource>> _sources;
  };
}