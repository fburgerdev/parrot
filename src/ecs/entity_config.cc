#include "common.hh"
#include "entity_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// EntityConfig
	EntityConfig::EntityConfig(const stdf::path& config_path)
		: UUIDObject(config_path) {
		loadFromJSON(json::parse(ifstream(config_path)), config_path);
	}
}