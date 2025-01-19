#include "common.hh"
#include "material.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// Material
	Material::Material(const stdf::path& filepath)
		: UUIDObject(filepath) {
		loadFromJSON(json::parse(ifstream(filepath)), filepath);
	}
}