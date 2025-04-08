#pragma once

namespace Parrot {
  // (constructor)
  template<class T>
  AssetHandle<T>::AssetHandle(UUID uuid, AssetAPI& asset_api)
    : _key(uuid), _api(&asset_api) {
  }
  template<class T>
  AssetHandle<T>::AssetHandle(const AssetPath& path, AssetAPI& asset_api)
    : _key(path), _api(&asset_api) {
  }
  template<class T>
  AssetHandle<T>::AssetHandle(const AssetKey& key, AssetAPI& asset_api)
    : _key(key), _api(&asset_api) {
  }
  template<class T>
  AssetHandle<T>::AssetHandle(const SerialNode& node, AssetAPI& asset_api)
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
  template<class T>
  AssetHandle<T>::operator bool() const {
    return _api;
  }
  // lock
  template<class T>
  SharedPtr<const T> AssetHandle<T>::lock() const {
    return std::static_pointer_cast<const T>(
      _api->lockAsset(_key, [&](const AssetPath& path) {
        return std::make_shared<T>(path, *_api);
        })
    );
  }
}