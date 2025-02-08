#pragma once
#include "core/asset_handle.hh"

namespace Parrot {
  // ShaderSource (Asset)
  class ShaderSource : public Asset {
  public:
    // (constructor)
    ShaderSource(const string& source);
    // :: for Asset
    ShaderSource(const AssetPath& asset_path, AssetAPI& asset_api);
    template<JsonType JSON>
    ShaderSource(
      const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
    ) : Asset(asset_path) {}

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
        VERTEX, FRAGMENT
      };

      // toString
      string toString() const {
        return "#version " + version + Snippet::toString();
      }

      // type, version
      Type type;
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
    ShaderProgram(const AssetPath& asset_path, AssetAPI& asset_api);
    template<JsonType JSON>
    ShaderProgram(
      const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json, asset_api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
      _sources.emplace_back(
        AssetPath(stdf::path(".parrot/model.glsl.macro")), asset_api
      );
      _sources.emplace_back(
        AssetPath(stdf::path(".parrot/surface.glsl.macro")), asset_api
      );
      if (json.contains("sources")) {
        for (const auto& source_json : json.at("sources")) {
          _sources.emplace_back(
            AssetPath(stdf::path(string(source_json))), asset_api
          );
        }
      }
    }

    // resolveShaderStages
    Pair<string, string> resolveShaderStages() const {
      // lock
      List<SharedPtr<ShaderSource>> locked_sources;
      for (const auto& source : _sources) {
        locked_sources.emplace_back(source.lock());
      }
      // merge
      ShaderSource::ShaderStage* vertex = nullptr;
      ShaderSource::ShaderStage* fragment = nullptr;
      Map<string, ShaderSource::Snippet*> snippets;
      for (auto& locked_source : locked_sources) {
        if (locked_source->vertex) {
          vertex = &locked_source->vertex.value();
        }
        if (locked_source->fragment) {
          fragment = &locked_source->fragment.value();
        }
        for (auto& [name, snippet] : locked_source->snippets) {
          snippets.emplace(name, &snippet);
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
              resolve(*snippets.at(include.identifier));
              part = snippets.at(include.identifier)->toString();
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
      resolve(*vertex);
      resolve(*fragment);

      return {
        vertex->toString(),
        fragment->toString()
      };
    }
  private:
    List<AssetHandle<ShaderSource>> _sources;
  };
}