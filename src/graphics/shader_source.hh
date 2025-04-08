#pragma once
#include "core/asset_handle.hh"
#include "core/log.hh"

namespace Parrot {
  class ShaderSource : public Asset {
  public:
    ShaderSource(const string& source);
    ShaderSource(const AssetPath& path, AssetAPI& api);
    ShaderSource(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    struct SnippetInclude {
      string identifier;
      bool is_optional = false;
    };
    struct Snippet {
      string toString() const;

      string name;
      List<Variant<SnippetInclude, string>> body;
    };
    struct ShaderStage : public Snippet {
      enum class Type {
        NONE = 0, VERTEX, FRAGMENT
      };

      string toString() const;

      Type type = Type::NONE;
      string version = "330 core";
    };

    Opt<ShaderStage> vertex, fragment;
    Map<string, Snippet> snippets;
  };

  class ShaderProgram : public Asset {
  public:
    ShaderProgram(const AssetPath& path, AssetAPI& api);
    ShaderProgram(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    Pair<string, string> resolveShaderStages() const;
  private:
    List<AssetHandle<ShaderSource>> _sources;
  };
}