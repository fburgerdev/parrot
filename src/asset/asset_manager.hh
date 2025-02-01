#pragma once
#include "core/asset_handle.hh"
#include "asset_registry.hh"
#include "asset_policy.hh"

namespace Parrot {
  // AssetManager
  class AssetManager : public AssetAPI {
  public:
    // (constructor)
    AssetManager() = default;
    AssetManager(const stdf::path& asset_dir);
    AssetManager(const stdf::path& asset_dir,
      LoadingPolicy loading_policy, UnloadingPolicy unloading_policy
    );
    // getAssetDirectory
    const stdf::path getAssetDirectory() const;

    // addAsset (impl. AssetAPI)
    virtual UUID addAsset(SharedPtr<Asset> asset) override;
    // lockAsset (impl. AssetAPI)
    virtual SharedPtr<Asset> lockAsset(
      const AssetKey& key, AssetFactory factory
    ) override;
  private:
    stdf::path _asset_dir;
    LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
    AssetRegistry _registry;
    Map<UUID, Variant<SharedPtr<Asset>, WeakPtr<Asset>>> _loaded;
  };
}