#pragma once
#include "mesh.hh"
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
			mesh = parseAssetHandle<Mesh>(json.at("mesh"), filepath);
			material = parseAssetHandle<Material>(json.at("material"), filepath);
		}

		// mesh, material
		AssetHandle<Mesh> mesh;
		AssetHandle<Material> material;
	};
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}