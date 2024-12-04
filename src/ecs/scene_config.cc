#include "common.hh"
#include "scene_config.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// SceneConfig
	SceneConfig::SceneConfig(const stdf::path& config_path) {
		loadFromJSON(json::parse(ifstream(config_path)));
	}
}