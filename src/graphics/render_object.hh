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
			const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
		) : Asset(asset_path) {
			loadFromJSON(json, asset_api);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
			model = AssetHandle<Model>(json.at("model"), asset_api);
			material = AssetHandle<Material>(json.at("material"), asset_api);
		}

		// model, material
		AssetHandle<Model> model;
		AssetHandle<Material> material;
	};
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}