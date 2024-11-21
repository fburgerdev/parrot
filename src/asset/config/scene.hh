#pragma once
#include "entity.hh"

namespace Parrot {
	// SceneConfig
	class SceneConfig {
	public:
		// SceneConfig
		template<class JSON>
		SceneConfig(const JSON& json) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// root
			if (scene.at("root").is_number()) {
				root = uuid(json.at("root"));
			}
			else if (scene.at("root").is_string()) {
				root = stdf::path(string(json.at("root")));
			}
			else {
				root = EntityConfig(json.at("root"));
			}
		}

		// name, root
		string name = "Unnamed Scene";
		Opt<Variant<uuid, stdf::path, EntityConfig>> root;
	};
}