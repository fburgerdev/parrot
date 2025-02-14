#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"

namespace Parrot {
  // StageConfig (Asset)
  class StageConfig : public Asset {
  public:
    // (constructor) for Asset
    StageConfig(const AssetPath& asset_path, AssetAPI& asset_api);
    template<JsonType JSON>
    StageConfig(
      const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json, asset_api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
      // window
      window = AssetHandle<WindowConfig>(json.at("window"), asset_api);
      // scenes
      if (json.contains("scene")) {
        scenes.emplace_back(
          AssetHandle<SceneConfig>(json.at("scene"), asset_api)
        );
      }
      if (json.contains("scenes")) {
        for (const auto& scene : json.at("scenes")) {
          scenes.emplace_back(
            AssetHandle<SceneConfig>(scene, asset_api)
          );
        }
      }
    }

    // window, scenes
    AssetHandle<WindowConfig> window;
    List<AssetHandle<SceneConfig>> scenes;
  };
}