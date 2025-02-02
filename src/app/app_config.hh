#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"
#include "asset/asset_policy.hh"

namespace Parrot {
  // AppConfig (Asset)
  class AppConfig : public Asset {
  public:
    // (constructor) for Asset
    AppConfig(const AssetPath& asset_path);
    AppConfig(const AssetPath& asset_path, AssetAPI& asset_api);
    template<JsonType JSON>
    AppConfig(
      const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json, asset_api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json) {
      // name
      if (json.contains("name")) {
        name = string(json.at("name"));
      }
      // asset_dir
      if (json.contains("asset_dir")) {
        asset_dir = stdf::path(string(json.at("asset_dir")));
      }
      if (asset_dir.is_relative()) {
        asset_dir = asset_path.file.parent_path() / asset_dir;
      }
      // asset-manager
      if (json.contains("asset-manager")) {
        const JSON& json_asset_manager = json.at("asset-manager");
        // (un)loading_policy
        if (json_asset_manager.contains("loading-policy")) {
          if (json_asset_manager.at("loading-policy") == "app") {
            // TODO: uncomment
            // loading_policy = LoadingPolicy::PRELOAD_APP;
          }
          else if (json_asset_manager.at("loading-policy") == "scene") {
            // TODO: uncomment
            // loading_policy = LoadingPolicy::PRELOAD_SCENE;
          }
          else if (json_asset_manager.at("loading-policy") == "lazy") {
            loading_policy = LoadingPolicy::LAZY_LOAD;
          }
        }
        if (json_asset_manager.contains("unloading-policy")) {
          if (json_asset_manager.at("unloading-policy") == "app") {
            unloading_policy = UnloadingPolicy::UNLOAD_APP;
          }
          else if (json_asset_manager.at("unloading-policy") == "scene") {
            // TODO: uncomment
            // unloading_policy = UnloadingPolicy::UNLOAD_SCENE;
          }
          else if (json_asset_manager.at("unloading-policy") == "unused") {
            unloading_policy = UnloadingPolicy::UNLOAD_UNUSED;
          }
        }
      }
    }
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
      loadFromJSON(json);
      // main (window / scene)
      main_window = AssetHandle<WindowConfig>(json.at("main")[0], asset_api);
      main_scene = AssetHandle<SceneConfig>(json.at("main")[1], asset_api);
    }

    // name, asset_dir, (un)loading_policy, main(window/scene)
    string name = "App";
    stdf::path asset_dir = ".";
    LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
    AssetHandle<WindowConfig> main_window;
    AssetHandle<SceneConfig> main_scene;
  };
}