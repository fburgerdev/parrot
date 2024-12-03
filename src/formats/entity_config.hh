#pragma once
#include "uuid.hh"

namespace Parrot {
	// EntityConfig
	class EntityConfig {
	public:
		// EntityConfig
		EntityConfig() = default;
		EntityConfig(const stdf::path& config_path);
		template<class JSON>
		EntityConfig(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON>
		void loadFromJSON(const JSON& json) {
			// tag
			if (json.contains("tag")) {
				tag = string(json.at("tag"));
			}
			// TODO: transform
			// children
			if (json.contains("children")) {
				for (const auto& child : json.at("children")) {
					if (child.is_number()) {
						children.emplace_back(uuid(child));
					}
					else if (child.is_string()) {
						children.emplace_back(stdf::path(string(child)));
					}
					else {
						children.emplace_back(EntityConfig(child));
					}
				}
			}
			// TODO: components
		}

		// tag, transform, children, components
		string tag = "Entity";
		// TODO: uncomment
		// Transform transform;
		List<Variant<uuid, stdf::path, EntityConfig>> children;
		// TODO: uncomment
		// Map<usize, Component> components;
	};
}