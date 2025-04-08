#pragma once
#include "asset.hh"
#include "asset_path.hh"

namespace Parrot {
  // AssetFactory
  using AssetFactory = Func<SharedPtr<Asset>(const AssetPath&)>;
  // AssetAPI
  class AssetAPI {
  public:
    // addAsset
    virtual UUID addAsset(SharedPtr<Asset> asset) = 0;
    // lockAsset
    virtual SharedPtr<const Asset> lockAsset(
      const AssetKey& key, AssetFactory factory
    ) = 0;
  };
  // AssetHandle
  template<class T>
  class AssetHandle {
  public:
    // (constructor)
    AssetHandle() = default;
    AssetHandle(UUID uuid, AssetAPI& asset_api);
    AssetHandle(const AssetPath& path, AssetAPI& asset_api);
    AssetHandle(const AssetKey& key, AssetAPI& asset_api);
    AssetHandle(const SerialNode& node, AssetAPI& asset_api) /* DEPRECATED */;

    // bool (cast)
    operator bool() const;
    // lock
    SharedPtr<const T> lock() const;
  private:
    AssetKey _key = UUID(0);
    AssetAPI* _api = nullptr;
  };
}
#define ASSET_HANDLE_HH
#include "asset_handle_impl.hh"