#pragma once
#include "uuid.hh"
#include "ecs/transform.hh"
#include "ecs/component_registry.hh"
#include "debug/debug.hh"

namespace Parrot {
	// EntityConfig
	class EntityConfig {
	public:
		// EntityConfig
		EntityConfig() = default;
		EntityConfig(const stdf::path& config_path);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		EntityConfig(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			// tag
			if (json.contains("tag")) {
				tag = string(json.at("tag"));
			}
			// transform
			if (json.contains("transform")) {
				if (json.at("transform").contains("position")) {
					transform.position = Vec3<float32>(
						json.at("transform").at("position")[0],
						json.at("transform").at("position")[1],
						json.at("transform").at("position")[2]
					);
				}
				if (json.at("transform").contains("rotation")) {
					transform.rotation = Vec3<float32>(
						json.at("transform").at("rotation")[0],
						json.at("transform").at("rotation")[1],
						json.at("transform").at("rotation")[2]
					);
				}
				if (json.at("transform").contains("scale")) {
					transform.scale = Vec3<float32>(
						json.at("transform").at("scale")[0],
						json.at("transform").at("scale")[1],
						json.at("transform").at("scale")[2]
					);
				}
			}
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
			// components
			if (json.contains("components")) {
				for (const auto& [name, data] : json.at("components").items()) {
					if (g_component_registry<JSON>.contains(name)) {
						components.emplace_back(g_component_registry<JSON>.at(name)(data));
					}
					else {
						LOG_ASSET_WARNING("unregistered component '{}' in json, will be ignored ", name);
					}
				}
			}
		}

		// tag, transform, children, components
		string tag = "Entity";
		Transform transform;
		List<Variant<uuid, stdf::path, EntityConfig>> children;
		List<UniquePtr<ComponentConfig>> components;
	};
}