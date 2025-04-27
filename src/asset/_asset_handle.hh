#pragma once
#include "core/factory.hh"
#include "core/asset_path.hh"
#include "_asset.hh"

namespace Parrot {
  class _IAssetManager {
  public:
    virtual SharedPtr<_Asset> lock(const AssetKey& key, const Factory<_Asset>& factory) = 0;
    virtual UUID addAsset(const AssetKey& key, _Asset& parent) = 0;
  };
  template<class T>// requires std::is_base_of_v<_Asset, T>
  class _AssetHandle {
  public:
    _AssetHandle() = default;

    SharedPtr<T> lock() const {
      auto lambda = [&]() {
        auto asset = UniquePtr<_Asset>(new T());
        asset->_manager = _manager;
        return asset;
      };
      return std::dynamic_pointer_cast<T>(
        _manager->lock(_key, LambdaFactory<_Asset>(lambda))
      );
    }

    friend class _AssetNode;
  private:
    _AssetHandle(_IAssetManager& manager)
      : _manager(&manager) {
    }
    _AssetHandle(const AssetKey& key, _IAssetManager& manager)
      : _key(key), _manager(&manager) {
    }

    AssetKey _key = UUID(0);
    _IAssetManager* _manager = nullptr;
  };
}