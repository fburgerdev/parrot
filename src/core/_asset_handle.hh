#pragma once
#include "_asset_manager.hh"
#include "asset_path.hh"

namespace Parrot {
  template<class T>
  class _AssetHandle {
  public:
    using Type = T;

    _AssetHandle() = default;

    SharedPtr<T> lock() const {
      if (!_manager) {
        return nullptr;
      }
      auto lambda = [&]() {
        if constexpr (requires { T{*_manager}; }) {
          return std::make_unique<T>(*_manager);
        }
        else {
          return std::make_unique<T>();
        }
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

  template<class T>
  constexpr bool IS_ASSET_HANDLE = false;
  template<class T>
  constexpr bool IS_ASSET_HANDLE<_AssetHandle<T>> = true;

  template<class T>
  concept AssetHandleType = IS_ASSET_HANDLE<T>;
}