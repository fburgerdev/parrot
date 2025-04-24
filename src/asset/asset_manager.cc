#include "common.hh"
#include "asset_manager.hh"
#include "core/log.hh"

namespace Parrot {
  //* Registry
  // (constructor)
  AssetManager::Registry::Registry(const stdf::path& asset_dir)
    : _asset_dir(asset_dir) {
    add(asset_dir);
  }

  // getUUID
  UUID AssetManager::Registry::getUUID(const AssetPath& asset_path) const {
    return _uuid_map.at(asset_path);
  }
  UUID AssetManager::Registry::getUUID(const AssetKey& key) const {
    if (holds<UUID>(key)) {
      return std::get<UUID>(key);
    }
    else {
      return getUUID(std::get<AssetPath>(key));
    }
  }
  // getAssetPath
  const AssetPath& AssetManager::Registry::getAssetPath(
    UUID uuid
  ) const {
    return _asset_path_map.at(uuid);
  }
  const AssetPath& AssetManager::Registry::getAssetPath(
    const AssetKey& key
  ) const {
    if (holds<UUID>(key)) {
      return getAssetPath(std::get<UUID>(key));
    }
    else {
      return std::get<AssetPath>(key);
    }
  }

  // contains
  bool AssetManager::Registry::contains(UUID uuid) const {
    return _asset_path_map.contains(uuid);
  }
  bool AssetManager::Registry::contains(const AssetPath& asset_path) const {
    return _uuid_map.contains(asset_path);
  }
  // find
  const AssetPath* AssetManager::Registry::find(UUID uuid) const {
    auto it = _asset_path_map.find(uuid);
    if (it != _asset_path_map.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }
  UUID AssetManager::Registry::find(const AssetPath& asset_path) const {
    auto it = _uuid_map.find(asset_path);
    if (it != _uuid_map.end()) {
      return it->second;
    }
    else {
      return 0;
    }
  }
  // add
  void AssetManager::Registry::add(UUID uuid, const AssetPath& asset_path) {
    _asset_path_map.emplace(uuid, asset_path);
    _uuid_map.emplace(asset_path, uuid);
  }
  void AssetManager::Registry::add(const stdf::path& path) {
    if (stdf::is_regular_file(path)) {
      if (path.extension().string() == ".json") {
        string source = (ostrstream() << ifstream(path).rdbuf()).str();
        auto json = SerialNode::loadFromJSON(path);
        if (json.contains("uuid")) {
          add(UUID(json.at("uuid")), stdf::relative(path, _asset_dir));
        }
        else {
          add(generateUUID(), stdf::relative(path, _asset_dir));
        }
      }
      else {
        add(generateUUID(), stdf::relative(path, _asset_dir));
      }
    }
    else if (stdf::is_directory(path)) {
      auto iterator = stdf::directory_iterator(path);
      for (auto entry : iterator) {
        add(entry.path());
      }
    }
  }
  void AssetManager::Registry::add(const AssetPath& asset_path) {
    auto json = asset_path.applySubpathToNode(
      SerialNode::loadFromJSON(asset_path.file)
    );
    if (json.contains("uuid")) {
      add(UUID(json.at("uuid")), asset_path);
    }
    else {
      // TODO: log warning
    }
  }
  // remove
  void AssetManager::Registry::remove(UUID uuid) {
    auto it = _asset_path_map.find(uuid);
    _uuid_map.erase(it->second);
    _asset_path_map.erase(it);
  }
  void AssetManager::Registry::remove(const AssetPath& asset_path) {
    auto it = _uuid_map.find(asset_path);
    _asset_path_map.erase(it->second);
    _uuid_map.erase(it);
  }

  //* AssetManager
  // (constructor)
  AssetManager::AssetManager(const stdf::path& asset_dir)
    : AssetManager(asset_dir,
      LoadingPolicy::LAZY_LOAD, UnloadingPolicy::UNLOAD_NEVER
  ) {}
  AssetManager::AssetManager(
    const stdf::path& asset_dir,
    LoadingPolicy load_policy,
    UnloadingPolicy unload_policy)
    : _asset_dir(asset_dir),
      _registry(asset_dir),
      _load_policy(load_policy),
      _unload_policy(unload_policy) {
    // TODO: assert(int(loading_policy) <= int(unloading_policy))
    LOG_ASSET_TRACE("asset-manager initialized with directory {}", asset_dir);
  }

  // getDirectory
  const stdf::path& AssetManager::getAssetDirectory() const {
    return _asset_dir;
  }

  // addAsset
  UUID AssetManager::addAsset(SharedPtr<Asset> asset) {
    UUID uuid = generateUUID();
    _registry.add(uuid, asset->getAssetPath());
    _loaded.emplace(uuid, asset);
    return uuid;
  }
  // lockAsset
  SharedPtr<const Asset> AssetManager::lockAsset(
    const AssetKey& key, AssetFactory factory
  ) {
    UUID uuid = _registry.getUUID(key);
    AssetPath asset_path = _registry.getAssetPath(key);
    asset_path.file = _asset_dir / asset_path.file;
    asset_path.debug_root = _asset_dir;
    auto it = _loaded.find(uuid);
    if (it == _loaded.end()) {
      auto asset = factory(asset_path);
      _loaded.emplace(uuid, SharedPtr<Asset>(asset));
      return asset;
    }
    else {
      if (holds<SharedPtr<Asset>>(it->second)) {
        return std::get<SharedPtr<Asset>>(it->second);
      }
      else if (!std::get<WeakPtr<Asset>>(it->second).expired()) {
        return std::get<WeakPtr<Asset>>(it->second).lock();
      }
      else {
        auto asset = factory(asset_path);
        it->second = SharedPtr<Asset>(asset);
        return asset;
      }
    }
  }
}