#include "common.hh"
#include "asset_index.hh"
#include "debug/engine_logger.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// AssetIndex
	AssetIndex::AssetIndex(const stdf::path& asset_dir)
		: _asset_dir(asset_dir) {
		LOG_ASSET_TRACE("indexing asset directory {}", asset_dir);
		for (stdf::path path : stdf::recursive_directory_iterator(asset_dir)) {
			if (stdf::is_regular_file(path)) {
				path = stdf::relative(stdf::canonical(path), asset_dir);
				UUID uuid = 0;
				if (path.extension().string().ends_with(".json")) {
					auto data = json::parse(ifstream(asset_dir / path));
					if (data.contains("uuid")) {
						uuid = data.at("uuid");
					}
					else {
						uuid = generateUUID();
					}
				}
				else {
					uuid = generateUUID();
				}
				_uuids.emplace(path, uuid);
				_paths.emplace(uuid, path);
			}
		}
		for (auto& [path, uuid] : _uuids) {
			LOG_ASSET_TRACE("indexed {} with {}", path, uuid);
		}
	}

	// index
	void AssetIndex::index(const stdf::path& path, UUID uuid) {
		stdf::path relative = stdf::relative(stdf::canonical(_asset_dir / path));
		_uuids.emplace(relative, uuid);
		_paths.emplace(uuid, relative);
	}
	// isIndexed
	bool AssetIndex::isIndexed(const stdf::path& path) const {
		return _uuids.contains(stdf::relative(stdf::canonical(_asset_dir / path), _asset_dir));
	}
	bool AssetIndex::isIndexed(UUID uuid) const {
		return _paths.contains(uuid);
	}

	// getUUID
	UUID AssetIndex::getUUID(const stdf::path& path) const {
		return _uuids.at(stdf::relative(stdf::canonical(_asset_dir / path), _asset_dir));
	}
	// getPath
	const stdf::path& AssetIndex::getPath(UUID uuid) const {
		return _paths.at(uuid);
	}
}