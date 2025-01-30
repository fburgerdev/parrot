#include "common.hh"
#include "material.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// Material
	Material::Material(const AssetPath& asset_path, AssetLocker& locker)
		: Asset(asset_path) {
		auto json = asset_path.applySubpathToJSON(
			json::parse(ifstream(asset_path.filepath))
		);
		loadFromJSON(json, locker);
	}
}