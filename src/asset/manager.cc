#include "common.hh"
#include "manager.hh"
#include "debug/debug.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// AssetIndex
	AssetIndex::AssetIndex(const stdf::path& asset_dir) {
		LOG_ASSET_TRACE("indexing asset directory {}", asset_dir);
		for (stdf::path path : stdf::recursive_directory_iterator(asset_dir)) {
			if (stdf::is_regular_file(path)) {
				if (path.extension().string().ends_with(".json")) {
					auto data = json::parse(ifstream(path));
					if (data.contains("uuid")) {
						_uuids.emplace(stdf::relative(path, asset_dir), uuid(data.at("uuid")));
						_paths.emplace(uuid(data.at("uuid")), stdf::relative(path, asset_dir));
					}
					else {
						LOG_ASSET_WARNING("asset {} does not have a \"uuid\" property, will not be indexed", stdf::relative(path, asset_dir));
					}
				}
			}
		}
		for (auto& [uuid, path] : _paths) {
			LOG_ASSET_TRACE("indexed {}", path);
		}
	}
	// getUUID
	uuid AssetIndex::getUUID(const stdf::path& path) const{
		return _uuids.at(path);
	}
	// getPath
	const stdf::path& AssetIndex::getPath(uuid uuid) const {
		return _paths.at(uuid);
	}

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
	bool AssetManager::isLoaded(uuid uuid) const {
		return _assets.contains(uuid);
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
	HandleResolver AssetManager::getHandleResolver() {
		return HandleResolver([&](
			const Variant<uuid, stdf::path>& variant,
			const function<Pair<void*, function<void()>>(stdf::path)>& create,
			const function<void(const void*)>& callback) {
				uuid deduced_uuid = std::holds_alternative<uuid>(variant) ? std::get<uuid>(variant) : _index.getUUID(std::get<stdf::path>(variant));
				if (!isLoaded(deduced_uuid)) {
					auto [value, delete_func] = create(_asset_dir / _index.getPath(deduced_uuid));
					_assets.emplace(deduced_uuid, Asset(value, (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED), delete_func));
				}
				callback(_assets.at(deduced_uuid).get());
			});
	}
}