#pragma once
#include "entity_config.hh"

namespace Parrot {
	// SceneConfig (Asset)
	class SceneConfig : public Asset {
	public:
		// (constructor) for Asset
		SceneConfig() = default;
		SceneConfig(const AssetPath& asset_path, AssetAPI& asset_api);
		template<JsonType JSON>
		SceneConfig(
			const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
		) : Asset(asset_path) {
			loadFromJSON(json, asset_api);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// root
			root = AssetHandle<EntityConfig>(json.at("root"), asset_api);
		}

		// name, root
		string name = "Unnamed Scene";
		AssetHandle<EntityConfig> root;
	};
}