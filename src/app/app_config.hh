#pragma once
#include "stage_config.hh"
#include "asset/asset_policy.hh"

namespace Parrot {
  class AppConfig : public Asset {
  public:
    AppConfig(const AssetPath& path);
    AppConfig(const AssetPath& path, AssetAPI& api);
    AppConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node);
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    string name = "App";
    stdf::path asset_dir = ".";
    LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_NEVER;
    AssetHandle<StageConfig> main_stage;
  };
}