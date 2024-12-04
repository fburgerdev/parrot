#include "common.hh"
#include "render_object.hh"
#include "debug/debug.hh"

namespace Parrot {
	// RenderObject
	RenderObject::RenderObject(uuid mesh_uuid, uuid material_uuid)
		: mesh_uuid(mesh_uuid), material_uuid(material_uuid) {}
	// getComponentID
	usize RenderObject::getComponentID() const {
		return typeid(RenderObject).hash_code();
	}
	// createComponent
	UniquePtr<Component> RenderObject::createComponent(Entity& entity) const {
		return std::make_unique<RenderObjectComponent>(*this, entity);
	}

	// update
	void RenderObjectComponent::update([[maybe_unused]] float32 delta_time) {
		LOG_ECS_TRACE("render-object-component update: {}", *this);
	}

	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object) {
		return stream << "RenderObject(mesh_uuid=" << render_object.mesh_uuid << ",material_uuid=" << render_object.material_uuid << ')';
	}
}