#include "common.hh"
#include "entity_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// EntityConfig
	EntityConfig::EntityConfig(const AssetPath& asset_path, AssetLocker& locker)
		: Asset(asset_path) {
		auto json = asset_path.applySubpathToJSON(
			json::parse(ifstream(asset_path.filepath))
		);
		loadFromJSON(json, locker);
	}
}