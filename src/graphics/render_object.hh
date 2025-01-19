#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
	// RenderObject
	struct RenderObject {
		// RenderObject
		RenderObject() = default;
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		RenderObject(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, const stdf::path& filepath) {
			model = parseAssetHandle<Model>(json.at("model"), filepath);
			material = parseAssetHandle<Material>(json.at("material"), filepath);
		}

		// model, material
		AssetHandle<Model> model;
		AssetHandle<Material> material;
	};
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}