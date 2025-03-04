#pragma once
#include "stage_config.hh"
#include "asset/asset_policy.hh"

namespace Parrot {
  // AppConfig (Asset)
  class AppConfig : public Asset {
  public:
    // (constructor)
    AppConfig(const AssetPath& path);
    // :: for Asset
    AppConfig(const AssetPath& path, AssetAPI& api);
    template<JsonType JSON>
    AppConfig(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json) {
      // name
      if (json.contains("name")) {
        name = string(json.at("name"));
      }
      // asset-dir
      if (json.contains("asset_dir")) {
        asset_dir = stdf::path(string(json.at("asset_dir")));
      }
      if (asset_dir.is_relative()) {
        asset_dir = asset_path.file.parent_path() / asset_dir;
      }
      // asset-manager
      if (json.contains("asset-manager")) {
        const JSON& json_asset_manager = json.at("asset-manager");
        // loading_policy
        if (json_asset_manager.contains("loading-policy")) {
          if (json_asset_manager.at("loading-policy") == "app") {
            // TODO: implement loading-policy 'app'
            // loading_policy = LoadingPolicy::PRELOAD_APP;
            LOG_ASSET_WARNING(
              "loading-policy 'app' is not yet implemented,"
              "falling back to 'lazy'"
            );
          }
          else if (json_asset_manager.at("loading-policy") == "scene") {
            // TODO: implement loading-policy 'scene'
            // loading_policy = LoadingPolicy::PRELOAD_SCENE;
            LOG_ASSET_WARNING(
              "loading-policy 'scene' is not yet implemented,"
              "falling back to 'lazy'"
            );
          }
          else if (json_asset_manager.at("loading-policy") == "lazy") {
            loading_policy = LoadingPolicy::LAZY_LOAD;
          }
        }
        // unloading-policy
        if (json_asset_manager.contains("unloading-policy")) {
          if (json_asset_manager.at("unloading-policy") == "app") {
            unloading_policy = UnloadingPolicy::UNLOAD_APP;
          }
          else if (json_asset_manager.at("unloading-policy") == "scene") {
            // TODO: implement unloading-policy 'scene'
            // unloading_policy = UnloadingPolicy::UNLOAD_SCENE;
            LOG_ASSET_WARNING(
              "unloading-policy 'scene' is not yet implemented,"
              "falling back to 'unused'"
            );
          }
          else if (json_asset_manager.at("unloading-policy") == "unused") {
            unloading_policy = UnloadingPolicy::UNLOAD_UNUSED;
          }
        }
      }
    }
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // name, asset-dir, asset-manager
      loadFromJSON(json);
      // stage
      main_stage = AssetHandle<StageConfig>(json.at("stage"), api);
    }

    // name, asset_dir, (un)loading_policy, main(window/scene)
    string name = "App";
    stdf::path asset_dir = ".";
    LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
    AssetHandle<StageConfig> main_stage;
  };
}