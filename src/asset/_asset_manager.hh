#pragma once
#include "_asset_handle.hh"
#include "_asset_node.hh"

namespace Parrot {
  class _RootNode : public _AssetNode {
  public:
    virtual bool loadAsset(const AssetPath& path) override {
      return false;
    }

    friend class _AssetManager;
  private:
    using _AssetNode::_AssetNode;
  };
  class _AssetManager : public _IAssetManager {
  public:
    _AssetManager()
      : _root(this) {}

    _RootNode& getAssetRoot() {
      return _root;
    }

    SharedPtr<_Asset> lock(UUID uuid, const Factory<_Asset>& factory) {
      auto it = _assets.find(uuid);
      if (it != _assets.end()) {
        if (auto* shared = std::get_if<SharedPtr<_Asset>>(&it->second)) {
          return *shared;
        }
        else if (!std::get<WeakPtr<_Asset>>(it->second).expired()) {
          return std::get<WeakPtr<_Asset>>(it->second).lock();
        }
      }
      auto asset = SharedPtr<_Asset>(factory.create());
      if (asset->loadAsset(_uuid_to_path.at(uuid))) {
        if (it != _assets.end()) {
          it->second = asset;
        }
        else {
          _assets.emplace(uuid, asset);
        }
        return asset;
      }
      else {
        throw;
      }
    }
    SharedPtr<_Asset> lock(const AssetPath& path, const Factory<_Asset>& factory) {
      return lock(add(path), factory);
    }
    virtual SharedPtr<_Asset> lock(const AssetKey& key, const Factory<_Asset>& factory) override {
      return std::visit([&](const auto& value) {
        return lock(value, factory);
      }, key);
    }

    virtual UUID addAsset(const AssetKey& key, _Asset& parent) override {
      if (auto* uuid = std::get_if<UUID>(&key)) {
        return *uuid;
      }
      else {
        return add(std::get<AssetPath>(key));
      }
    }

    UUID add(const AssetPath& path) {
      auto it = _path_to_uuid.find(path);
      if (it == _path_to_uuid.end()) {
        UUID uuid = generateUUID();
        _uuid_to_path.emplace(uuid, path);
        _path_to_uuid.emplace(path, uuid);
        return uuid;
      }
      else {
        return it->second;
      }
    }
  private:
    _RootNode _root;
    HashMap<UUID, AssetPath> _uuid_to_path;
    Map<AssetPath, UUID> _path_to_uuid;
    HashMap<UUID, Variant<SharedPtr<_Asset>, WeakPtr<_Asset>>> _assets;
  };
}