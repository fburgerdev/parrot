#pragma once
#include "asset_handle.hh"
#include "registry.hh"
#include "component.hh"
#include "math/math3d.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
	// EntityConfig
	class EntityConfig : public UUIDObject {
	public:
		// EntityConfig
		EntityConfig() = default;
		EntityConfig(const stdf::path& config_path);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		EntityConfig(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, const stdf::path& filepath) {
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
					children.emplace_back(parseAssetHandle<EntityConfig>(child, filepath));
				}
			}
			// components
			if (json.contains("components")) {
				for (const auto& [name, data] : json.at("components").items()) {
					if (g_registry<ComponentConfig, const JSON&, const stdf::path&>.contains(name)) {
						components.emplace_back(
							g_registry<ComponentConfig, const JSON&, const stdf::path&>.at(name).second(data, filepath)
						);
					}
					else {
						LOG_ASSET_WARNING("unregistered component '{}' in json, will be ignored ", name);
					}
				}
			}
			// scripts
			if (json.contains("scripts")) {
				for (const auto& script : json.at("scripts")) {
					scripts.emplace_back(string(script));
				}
			}
		}
		
		// tag, transform, children, components, scripts
		string tag = "Entity";
		Transform<> transform;
		List<AssetHandle<EntityConfig>> children;
		List<UniquePtr<ComponentConfig>> components;
		List<string> scripts;
	};
}