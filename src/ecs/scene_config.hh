#pragma once
#include "entity_preset.hh"

namespace Parrot {
  // SceneConfig (Asset)
  class SceneConfig : public Asset {
  public:
    // (constructor) for Asset
    SceneConfig(const AssetPath& path, AssetAPI& apit);
    SceneConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
      // name
      if (node.contains("name")) {
        name = string(node.at("name"));
      }
      // root
      root = AssetHandle<EntityPreset>(node.at("root"), api);
      // scripts
      if (node.contains("scripts")) {
        for (const auto& script : node.at("scripts")) {
          scripts.emplace_back(string(script));
        }
      }
    }

    // name, root, scripts
    string name = "Unnamed Scene";
    AssetHandle<EntityPreset> root;
    List<string> scripts;
  };
}