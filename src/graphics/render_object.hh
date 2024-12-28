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
			mesh = parseHandleFromJSON<Mesh>(json.at("mesh"), filepath);
			material = parseHandleFromJSON<Material>(json.at("material"), filepath);
		}

		// mesh, material
		Handle<Mesh> mesh;
		Handle<Material> material;
	};
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}