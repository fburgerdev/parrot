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
    AppConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node);
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // name, asset_dir, (un)loading_policy, main(window/scene)
    string name = "App";
    stdf::path asset_dir = ".";
    LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
    AssetHandle<StageConfig> main_stage;
  };
}