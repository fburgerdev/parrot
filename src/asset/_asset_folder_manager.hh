#pragma once
#include "core/_asset_handle.hh"
#include "core/_asset_node.hh"

namespace Parrot {
  class _AssetFolderRoot : public _AssetNode<> {
  public:
    virtual bool loadAsset(const AssetPath& path) override {
      return false;
    }

    friend class _AssetFolderManager;
  private:
    using _AssetNode<>::_AssetNode;
  };
  class _AssetFolderManager : public _AssetManager {
  public:
    _AssetFolderManager(const stdf::path& asset_dir)
      : _root(this), _registry(asset_dir) {
      _ASSERT(stdf::is_directory(asset_dir));
    }

    const stdf::path& getAssetDirectory() {
      return _registry.getRoot();
    }

    _AssetFolderRoot& getAssetRoot() {
      return _root;
    }

    virtual Deserializer& getDeserializer() {
      return _deserializer;
    }
  private:
    class Registry {
    public:
      Registry(const stdf::path& root)
        : _root(root) {}

      const stdf::path& getRoot() const {
        return _root;
      }

      bool contains(const AssetKey& key) const {
        if (holds<UUID>(key)) {
          return _uuid_to_path.contains(std::get<UUID>(key));
        }
        else {
          return _path_to_uuid.contains(normalize(std::get<AssetPath>(key)));
        }
      }
      UUID operator[](const AssetPath& path) {
        AssetPath normalized = normalize(path);
        auto it = _path_to_uuid.find(normalized);
        if (it == _path_to_uuid.end()) {
          UUID uuid = generateUUID();
          _uuid_to_path.emplace(uuid, normalized);
          _path_to_uuid.emplace(normalized, uuid);
          return uuid;
        }
        else {
          return it->second;
        }
      }
      const AssetPath& at(UUID uuid) {
        return _uuid_to_path.at(uuid);
      }
    private:
      AssetPath normalize(const AssetPath& path) const {
        AssetPath normalized = path;
        if (normalized.file.is_relative()) {
          normalized.file = stdf::canonical(_root / normalized.file);
        }
        else {
          _ASSERT(!stdf::relative(normalized.file, _root).empty());
          normalized.file = stdf::canonical(normalized.file);
        }
        return normalized;
      }

      stdf::path _root;
      HashMap<UUID, AssetPath> _uuid_to_path;
      Map<AssetPath, UUID> _path_to_uuid; // TOOD: Map -> HashMap
    };

    virtual AssetRef lockAsset(const AssetKey& key, const Factory<_Asset>& factory) override {
      return std::visit([&](const auto& value) {
        return lockAsset(value, factory);
      }, key);
    }
    AssetRef lockAsset(UUID uuid, const Factory<_Asset>& factory) {
      auto it = _assets.find(uuid);
      if (it != _assets.end()) {
        if (auto* shared = std::get_if<SharedPtr<_Asset>>(&it->second)) {
          return *shared;
        }
        else if (!std::get<WeakPtr<_Asset>>(it->second).expired()) {
          return std::get<WeakPtr<_Asset>>(it->second).lock();
        }
      }
      auto asset = AssetRef(factory.create());
      if (asset->loadAsset(_registry.at(uuid))) {
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
    AssetRef lockAsset(const AssetPath& path, const Factory<_Asset>& factory) {
      return lockAsset(_registry[path], factory);
    }

    virtual UUID registerAsset(const AssetKey& key, _Asset& parent) override {
      if (holds<UUID>(key)) {
        return std::get<UUID>(key);
      }
      else {
        return _registry[std::get<AssetPath>(key)];
      }
    }

    _AssetFolderRoot _root;
    Deserializer _deserializer;
    Registry _registry;
    HashMap<UUID, List<UUID>> _dependencies;
    HashMap<UUID, Variant<SharedPtr<_Asset>, WeakPtr<_Asset>>> _assets;
  };
}