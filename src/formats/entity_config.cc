#include "common.hh"
#include "entity_config.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// EntityConfig
	EntityConfig::EntityConfig(const stdf::path& config_path) {
		loadFromJSON(json::parse(ifstream(config_path)));
	}
}