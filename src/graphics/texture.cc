#include "common.hh"
#include "texture.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// Texture
	Texture::Texture(const stdf::path& filepath) {
		loadFromJSON(json::parse(ifstream(filepath)));
	}
}