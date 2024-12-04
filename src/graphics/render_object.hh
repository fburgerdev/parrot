#pragma once
#include "uuid.hh"

namespace Parrot {
	// RenderObject
	struct RenderObject {
		// RenderObject
		RenderObject(uuid mesh_uuid, uuid material_uuid);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		RenderObject(const JSON& json) {
			loadFromJSON(json);
		}
		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			mesh_uuid = json.at("mesh_uuid");
			material_uuid = json.at("material_uuid");
		}

		// mesh_uuid, material_uuid
		uuid mesh_uuid = 0, material_uuid = 0;
	};
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}