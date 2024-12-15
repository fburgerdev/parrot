#include "common.hh"
#include "app_config.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// AppConfig
	AppConfig::AppConfig(const stdf::path& config_path)
		: UUIDObject(config_path) {
		loadFromJSON(json::parse(ifstream(config_path)), config_path);
	}
}