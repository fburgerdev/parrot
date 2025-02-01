#include "common.hh"
#include "asset_manager.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
  // (constructor)
  AssetManager::AssetManager(const stdf::path& asset_dir)
    : AssetManager(asset_dir,
      LoadingPolicy::LAZY_LOAD, UnloadingPolicy::UNLOAD_APP
  ) {}
  AssetManager::AssetManager(
    const stdf::path& asset_dir,
    LoadingPolicy loading_policy,
    UnloadingPolicy unloading_policy)
    : _asset_dir(asset_dir),
      _registry(asset_dir),
      _loading_policy(loading_policy),
      _unloading_policy(unloading_policy) {
    // TODO: assert(int(loading_policy) <= int(unloading_policy))
    LOG_ASSET_TRACE("asset-manager initialized with directory {}", asset_dir);
  }

  // getDirectory
  const stdf::path AssetManager::getAssetDirectory() const {
    return _asset_dir;
  }

  // lockAsset
  SharedPtr<Asset> AssetManager::lockAsset(
    const AssetKey& key, AssetFactory factory
  ) {
    UUID uuid = _registry.getUUID(key);
    AssetPath asset_path = _registry.getAssetPath(key);
    asset_path.file = _asset_dir / asset_path.file;
    auto it = _loaded.find(uuid);
    if (it == _loaded.end()) {
      auto asset = factory(asset_path);
      _loaded.emplace(uuid, SharedPtr<Asset>(asset));
      return asset;
    }
    else {
      if (std::holds_alternative<SharedPtr<Asset>>(it->second)) {
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
  // addAsset
  UUID AssetManager::addAsset(SharedPtr<Asset> asset) {
    UUID uuid = generateUUID();
    _registry.add(uuid, asset->asset_path);
    _loaded.emplace(uuid, asset);
    return uuid;
  }
}