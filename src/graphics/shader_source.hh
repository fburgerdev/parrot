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
    ShaderSource(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // SnippetInclude
    struct SnippetInclude {
      // identifier, is_optional
      string identifier;
      bool is_optional = false;
    };
    // Snippet
    struct Snippet {
      // toString
      string toString() const;

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
      string toString() const;

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
    ShaderProgram(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    // resolveShaderStages
    Pair<string, string> resolveShaderStages() const;
  private:
    List<AssetHandle<ShaderSource>> _sources;
  };
}