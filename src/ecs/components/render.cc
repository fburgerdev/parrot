#include "common.hh"
#include "render.hh"

namespace Parrot {
	// RenderComponent
	RenderComponent::RenderComponent(Entity& entity, uuid mesh_uuid, uuid material_uuid)
		: Component(entity), mesh_uuid(mesh_uuid), material_uuid(material_uuid) {}
}