#include "common.hh"
#include "manager.hh"
#include "debug/debug.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// AssetIndex
	AssetIndex::AssetIndex(const stdf::path& asset_dir) {
		LOG_ASSET_TRACE("indexing asset directory {}", asset_dir);
		for (stdf::path path : stdf::recursive_directory_iterator(asset_dir)) {
			if (stdf::is_regular_file(path)) {
				if (path.extension().string().ends_with(".json") && !path.string().ends_with(".app.json")) {
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
	uuid AssetIndex::getUUID(const stdf::path& path) {
		if (!_uuids.contains(path)) {
			uuid uuid = generateUUID();
			_uuids.emplace(path, uuid);
			_paths.emplace(uuid, path);
		}
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
		// TODO: assert loading_policy <= unloading_policy
		LOG_ASSET_TRACE("asset-manager initialized with directory {}", asset_dir);
	}
}