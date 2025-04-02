#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"

namespace Parrot {
  // StageConfig (Asset)
  class StageConfig : public Asset {
  public:
    // (constructor) for Asset
    StageConfig(const AssetPath& path, AssetAPI& api);
    StageConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
      // window
      window = AssetHandle<WindowConfig>(node.at("window"), api);
      // scene(s)
      if (node.contains("scene")) {
        scenes.emplace_back(
          AssetHandle<SceneConfig>(node.at("scene"), api)
        );
      }
      if (node.contains("scenes")) {
        for (const auto& scene : node.at("scenes")) {
          scenes.emplace_back(
            AssetHandle<SceneConfig>(scene, api)
          );
        }
      }
      // scripts
      if (node.contains("scripts")) {
        for (const auto& script : node.at("scripts")) {
          scripts.emplace_back(string(script));
        }
      }
    }

    // window, scenes, scripts
    AssetHandle<WindowConfig> window;
    List<AssetHandle<SceneConfig>> scenes;
    List<string> scripts;
  };
}