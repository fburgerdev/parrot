#pragma once
#include "entity_config.hh"

namespace Parrot {
	// SceneConfig (Asset)
	class SceneConfig : public Asset {
	public:
		// (constructor) for Asset
		SceneConfig() = default;
		SceneConfig(const AssetPath& asset_path, AssetLocker& locker);
		template<JsonType JSON>
		SceneConfig(
			const JSON& json, const AssetPath& asset_path, AssetLocker& locker
		) : Asset(asset_path) {
			loadFromJSON(json, locker);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetLocker& locker) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// root
			root = AssetHandle<EntityConfig>(json.at("root"), locker);
		}

		// name, root
		string name = "Unnamed Scene";
		AssetHandle<EntityConfig> root;
	};
}