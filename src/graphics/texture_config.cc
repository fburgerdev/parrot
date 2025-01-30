#include "common.hh"
#include "texture_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// TextureConfig
	TextureConfig::TextureConfig(const AssetPath& asset_path, AssetLocker& locker)
		: Asset(asset_path) {
		auto json = asset_path.applySubpathToJSON(
			json::parse(ifstream(asset_path.filepath))
		);
		loadFromJSON(json, locker);
	}
	TextureConfig::TextureConfig(AssetHandle<Image> image)
		: image(std::move(image)) {}
}