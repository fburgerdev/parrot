#include "common.hh"
#include "window_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// WindowConfig
	WindowConfig::WindowConfig(const AssetPath& asset_path, AssetAPI& asset_api)
		: Asset(asset_path) {
		auto json = asset_path.applySubpathToJSON(
			json::parse(ifstream(asset_path.filepath))
		);
		loadFromJSON(json, asset_api);
	}
}