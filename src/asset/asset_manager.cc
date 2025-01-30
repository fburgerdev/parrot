#include "common.hh"
#include "asset_manager.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
	// AssetManager
	AssetManager::AssetManager(const stdf::path& asset_dir)
		: AssetManager(asset_dir, LoadingPolicy::LAZY_LOAD, UnloadingPolicy::UNLOAD_APP) {}
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

	// getAssetDirectory
	const stdf::path AssetManager::getAssetDirectory() const {
		return _asset_dir;
	}

	// // isLoaded
	// bool AssetManager::isLoaded(UUID uuid) const {
	// 	return _assets.contains(uuid);
	// }
	// bool AssetManager::isLoaded(const stdf::path& path) const {
	// 	return _assets.contains(_index.getUUID(path));
	// }
	// bool AssetManager::isLoaded(const Variant<UUID, stdf::path>& variant) const {
	// 	return std::visit([&](const auto& value) {
	// 		return isLoaded(value);
	// 		}, variant);
	// }

	// // getHandleResolver
	// AssetHandleResolver AssetManager::getHandleResolver() {
	// 	return AssetHandleResolver([&](
	// 		const Variant<UUID, stdf::path>& variant,
	// 		const Func<Pair<void*, Func<void()>>(stdf::path)>& create,
	// 		const Func<void(const void*)>& callback) {
	// 			UUID uuid = std::holds_alternative<UUID>(variant) ? std::get<UUID>(variant) : _index.getUUID(std::get<stdf::path>(variant));
	// 			if (!isLoaded(uuid)) {
	// 				auto [value, delete_func] = create(_asset_dir / _index.getPath(uuid));
	// 				_assets.emplace(uuid, AssetResource(value, (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED), delete_func));
	// 			}
	// 			callback(_assets.at(uuid).get());
	// 		});
	// }
	// // createAssetResolver
	// AssetResolver AssetManager::createAssetResolver() {
	// 	return [&] (const AssetKey& key) {
  //     if (loadedAsset(key)) {
  //       return getAsset(key);
  //     }
  //     else {
        
  //     }
  //     return lockAsset<Asset>(key);
	// 	};
	// }
}