#pragma once
#include "core/factory.hh"
#include "core/asset_path.hh"
#include "_asset_manager.hh"

namespace Parrot {
  template<class T>// requires std::is_base_of_v<_Asset, T>
  class _AssetHandle {
  public:
    _AssetHandle() = default;

    SharedPtr<T> lock() const {
      if (!_manager) {
        return nullptr;
      }
      auto lambda = [&]() {
        auto asset = UniquePtr<_Asset>(new T());
        asset->_manager = _manager;
        return asset;
      };
      return std::dynamic_pointer_cast<T>(
        _manager->lockAsset(_key, LambdaFactory<_Asset>(lambda))
      );
    }

    operator bool() const {
      return _manager;
    }

    template<class T>
    friend class _AssetNode;
  private:
    _AssetHandle(_AssetManager& manager)
      : _manager(&manager) {
    }
    _AssetHandle(const AssetKey& key, _AssetManager& manager)
      : _key(key), _manager(&manager) {
    }

    AssetKey _key = UUID(0);
    _AssetManager* _manager = nullptr;
  };
}