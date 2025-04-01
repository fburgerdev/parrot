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
    template<JsonType JSON>
    AssetHandle(const JSON& json, AssetAPI& asset_api) /* DEPRECATED */
      : _api(&asset_api) {
      if (json.is_number()) {
        _key = UUID(json);
      }
      else if (json.is_string()) {
        _key = AssetPath(strview(string(json)));
      }
      else {
        _key = _api->addAsset(std::make_shared<T>(json, stdf::path(), *_api));
      }
    }
    AssetHandle(const SerialNode& json, AssetAPI& asset_api) /* DEPRECATED */
      : _api(&asset_api) {
      if (json.isNumber()) {
        _key = UUID(json);
      }
      else if (json.isString()) {
        _key = AssetPath(strview(string(json)));
      }
      else {
        _key = _api->addAsset(std::make_shared<T>(json, stdf::path(), *_api));
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