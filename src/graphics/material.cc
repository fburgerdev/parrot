#include "common.hh"
#include "material.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// Material
	Material::Material(const stdf::path& filepath)
		: UUIDObject(filepath) {
		loadFromJSON(json::parse(ifstream(filepath)));
	}
}