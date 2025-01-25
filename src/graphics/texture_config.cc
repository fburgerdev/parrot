#include "common.hh"
#include "texture_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// TextureConfig
	TextureConfig::TextureConfig(const stdf::path& filepath)
		: UUIDObject(filepath) {
		loadFromJSON(json::parse(ifstream(filepath)), filepath);
	}
	TextureConfig::TextureConfig(AssetHandle<Image> image)
		: image(std::move(image)) {}
}