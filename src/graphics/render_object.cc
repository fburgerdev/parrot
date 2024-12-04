#include "common.hh"
#include "render_object.hh"
#include "debug/debug.hh"

namespace Parrot {
	// RenderObject
	RenderObject::RenderObject(uuid mesh_uuid, uuid material_uuid)
		: mesh_uuid(mesh_uuid), material_uuid(material_uuid) {}
	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object) {
		return stream << "RenderObject(mesh_uuid=" << render_object.mesh_uuid << ",material_uuid=" << render_object.material_uuid << ')';
	}
}