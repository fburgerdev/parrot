#pragma once
#include "entity_config.hh"

namespace Parrot {
	// SceneConfig
	class SceneConfig : public UUIDObject {
	public:
		// SceneConfig
		SceneConfig() = default;
		SceneConfig(const stdf::path& config_path);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		SceneConfig(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, const stdf::path& filepath) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// root
			root = parseHandleFromJSON<EntityConfig>(json.at("root"), filepath);
		}

		// name, root
		string name = "Unnamed Scene";
		Handle<EntityConfig> root;
	};
}