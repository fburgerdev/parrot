#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"

namespace Parrot {
  // StageConfig (Asset)
  class StageConfig : public Asset {
  public:
    // (constructor) for Asset
    StageConfig(const AssetPath& path, AssetAPI& api);
    template<JsonType JSON>
    StageConfig(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // window
      window = AssetHandle<WindowConfig>(json.at("window"), api);
      // scene(s)
      if (json.contains("scene")) {
        scenes.emplace_back(
          AssetHandle<SceneConfig>(json.at("scene"), api)
        );
      }
      if (json.contains("scenes")) {
        for (const auto& scene : json.at("scenes")) {
          scenes.emplace_back(
            AssetHandle<SceneConfig>(scene, api)
          );
        }
      }
      // scripts
      if (json.contains("scripts")) {
        for (const auto& script : json.at("scripts")) {
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