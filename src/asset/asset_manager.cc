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
		  _loading_policy(loading_policy),
		  _unloading_policy(unloading_policy),
		  _index(asset_dir) {
		// TODO: assert(int(loading_policy) <= int(unloading_policy))
		LOG_ASSET_TRACE("asset-manager initialized with directory {}", asset_dir);
	}

	// isLoaded
	bool AssetManager::isLoaded(uuid id) const {
		return _assets.contains(id);
	}
	bool AssetManager::isLoaded(const stdf::path& path) const {
		return _assets.contains(_index.getUUID(path));
	}
	bool AssetManager::isLoaded(const Variant<uuid, stdf::path>& variant) const {
		return std::visit([&](const auto& value) {
			return isLoaded(value);
			}, variant);
	}

	// getHandleResolver
	AssetHandleResolver AssetManager::getHandleResolver() {
		return AssetHandleResolver([&](
			const Variant<uuid, stdf::path>& variant,
			const function<Pair<void*, function<void()>>(stdf::path)>& create,
			const function<void(const void*)>& callback) {
				uuid id = std::holds_alternative<uuid>(variant) ? std::get<uuid>(variant) : _index.getUUID(std::get<stdf::path>(variant));
				if (!isLoaded(id)) {
					auto [value, delete_func] = create(_asset_dir / _index.getPath(id));
					_assets.emplace(id, AssetResource(value, (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED), delete_func));
				}
				callback(_assets.at(id).get());
			});
	}
}