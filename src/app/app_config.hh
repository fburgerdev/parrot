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
    AppConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node) {
      // name
      if (node.contains("name")) {
        name = string(node.at("name"));
      }
      // asset-dir
      if (node.contains("asset_dir")) {
        asset_dir = stdf::path(string(node.at("asset_dir")));
      }
      if (asset_dir.is_relative()) {
        asset_dir = getAssetPath().file.parent_path() / asset_dir;
      }
      // asset-manager
      if (node.contains("asset-manager")) {
        const SerialNode& node_asset_manager = node.at("asset-manager");
        // loading_policy
        if (node_asset_manager.contains("loading-policy")) {
          if (node_asset_manager.at("loading-policy") == "app") {
            // TODO: implement loading-policy 'app'
            // loading_policy = LoadingPolicy::PRELOAD_APP;
            LOG_ASSET_WARNING(
              "loading-policy 'app' is not yet implemented,"
              "falling back to 'lazy'"
            );
          }
          else if (node_asset_manager.at("loading-policy") == "scene") {
            // TODO: implement loading-policy 'scene'
            // loading_policy = LoadingPolicy::PRELOAD_SCENE;
            LOG_ASSET_WARNING(
              "loading-policy 'scene' is not yet implemented,"
              "falling back to 'lazy'"
            );
          }
          else if (node_asset_manager.at("loading-policy") == "lazy") {
            loading_policy = LoadingPolicy::LAZY_LOAD;
          }
        }
        // unloading-policy
        if (node_asset_manager.contains("unloading-policy")) {
          if (node_asset_manager.at("unloading-policy") == "app") {
            unloading_policy = UnloadingPolicy::UNLOAD_APP;
          }
          else if (node_asset_manager.at("unloading-policy") == "scene") {
            // TODO: implement unloading-policy 'scene'
            // unloading_policy = UnloadingPolicy::UNLOAD_SCENE;
            LOG_ASSET_WARNING(
              "unloading-policy 'scene' is not yet implemented,"
              "falling back to 'unused'"
            );
          }
          else if (node_asset_manager.at("unloading-policy") == "unused") {
            unloading_policy = UnloadingPolicy::UNLOAD_UNUSED;
          }
        }
      }
    }
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
      // name, asset-dir, asset-manager
      loadFromSerialNode(node);
      // stage
      main_stage = AssetHandle<StageConfig>(node.at("stage"), api);
    }

    // name, asset_dir, (un)loading_policy, main(window/scene)
    string name = "App";
    stdf::path asset_dir = ".";
    LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
    AssetHandle<StageConfig> main_stage;
  };
}