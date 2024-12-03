#pragma once
#include "entity_config.hh"

namespace Parrot {
	// SceneConfig
	class SceneConfig {
	public:
		// SceneConfig
		SceneConfig() = default;
		SceneConfig(const stdf::path& config_path);
		template<class JSON>
		SceneConfig(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON>
		void loadFromJSON(const JSON& json) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// root
			if (json.at("root").is_number()) {
				root.emplace(uuid(json.at("root")));
			}
			else if (json.at("root").is_string()) {
				root.emplace(stdf::path(string(json.at("root"))));
			}
			else {
				root.emplace(EntityConfig(json.at("root")));
			}
		}

		// name, root
		string name = "Unnamed Scene";
		Opt<Variant<uuid, stdf::path, EntityConfig>> root;
	};
}