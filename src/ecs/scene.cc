#include "common.hh"
#include "scene.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// Scene
	Scene::Scene(const stdf::path& filepath) {
		if (filepath.string().ends_with(".json")) {
			auto data = json::parse(ifstream(filepath));
			// name
			_name = data.contains("name") ? data.at("name") : "Unnamed Scene";
		}
	}
}