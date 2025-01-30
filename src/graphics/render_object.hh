#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
	// RenderObject (SubAsset)
	struct RenderObject : public Asset {
		// (constructor) for SubAsset
		RenderObject() = default;
		template<JsonType JSON>
		RenderObject(
			const JSON& json, const AssetPath& asset_path, AssetLocker& locker
		) : Asset(asset_path) {
			loadFromJSON(json, locker);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetLocker& locker) {
			model = AssetHandle<Model>(json.at("model"), locker);
			material = AssetHandle<Material>(json.at("material"), locker);
		}

		// model, material
		AssetHandle<Model> model;
		AssetHandle<Material> material;
	};
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}