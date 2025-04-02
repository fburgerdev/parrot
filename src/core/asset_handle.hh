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
    virtual UUID addAsset(SharedPtr<Asset> asset) = 0; /* API */
    // lockAsset
    virtual SharedPtr<const Asset> lockAsset(
      const AssetKey& key, AssetFactory factory
    ) = 0; /* API */
  };
  // AssetHandle
  template<class T>
  class AssetHandle {
  public:
    // (constructor)
    AssetHandle() = default;
    AssetHandle(UUID uuid, AssetAPI& asset_api)
      : _key(uuid), _api(&asset_api) {}
    AssetHandle(const AssetPath& path, AssetAPI& asset_api)
      : _key(path), _api(&asset_api) {}
    AssetHandle(const AssetKey& key, AssetAPI& asset_api)
      : _key(key), _api(&asset_api) {}
    AssetHandle(const SerialNode& node, AssetAPI& asset_api) /* DEPRECATED */
      : _api(&asset_api) {
      if (node.isNumber()) {
        _key = UUID(node);
      }
      else if (node.isString()) {
        _key = AssetPath(strview(string(node)));
      }
      else {
        _key = _api->addAsset(std::make_shared<T>(node, stdf::path(), *_api));
      }
    }


    // bool (cast)
    operator bool() const {
      return _api;
    }
    // lock
    SharedPtr<const T> lock() const {
      return std::static_pointer_cast<const T>(
        _api->lockAsset(_key, [&](const AssetPath& path) {
          return std::make_shared<T>(path, *_api);
        })
      );
    }
  private:
    AssetKey _key = UUID(0);
    AssetAPI* _api = nullptr;
  };
}