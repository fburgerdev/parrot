#pragma once
#include "uuid.hh"

namespace Parrot {
	// EntityConfig
	class EntityConfig {
	public:
		// EntityConfig
		template<class JSON>
		EntityConfig(const JSON& json) {
			// tag
			if (json.contains("tag")) {
				tag = string(json.at("tag"));
			}
			// children
			if (json.contains("children")) {
				for (const auto& child : json.at("children")) {
					if (child.is_number()) {
						children.emplace(uuid(child));
					}
					else if (child.is_string()) {
						children.emplace(string(child));
					}
					else {
						children.emplace(EntityConfig(child));
					}
				}
			}
		}

		// tag, transform, children, components
		string tag = "Entity";
		//Transform transform;
		Set<Variant<uuid, stdf::path, EntityConfig>> children;
		//Map<usize, Component> components;
	};
}