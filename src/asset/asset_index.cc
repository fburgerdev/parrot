#include "common.hh"
#include "asset_index.hh"
#include "debug/engine_logger.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// AssetIndex
	AssetIndex::AssetIndex(const stdf::path& asset_dir)
		: _asset_dir(asset_dir) {
		LOG_ASSET_TRACE("indexing asset directory {}", asset_dir);
		for (stdf::path path : stdf::recursive_directory_iterator(asset_dir)) {
			if (stdf::is_regular_file(path)) {
				path = stdf::relative(stdf::canonical(path), asset_dir);
				uuid id = 0;
				if (path.extension().string().ends_with(".json")) {
					auto data = json::parse(ifstream(path));
					if (data.contains("uuid")) {
						id = data.at("uuid");
					}
					else {
						id = generateUUID();
					}
				}
				else {
					id = generateUUID();
				}
				_uuids.emplace(path, id);
				_paths.emplace(id, path);
			}
		}
		for (auto& [path, id] : _uuids) {
			LOG_ASSET_TRACE("indexed {} with {}", path, id);
		}
	}

	// index
	void AssetIndex::index(const stdf::path& path, uuid id) {
		stdf::path relative = stdf::relative(stdf::canonical(_asset_dir / path));
		_uuids.emplace(relative, id);
		_paths.emplace(id, relative);
	}
	// isIndexed
	bool AssetIndex::isIndexed(const stdf::path& path) const {
		return _uuids.contains(stdf::relative(stdf::canonical(_asset_dir / path), _asset_dir));
	}
	bool AssetIndex::isIndexed(uuid id) const {
		return _paths.contains(id);
	}

	// getUUID
	uuid AssetIndex::getUUID(const stdf::path& path) const {
		return _uuids.at(stdf::relative(stdf::canonical(_asset_dir / path), _asset_dir));
	}
	// getPath
	const stdf::path& AssetIndex::getPath(uuid id) const {
		return _paths.at(id);
	}
}