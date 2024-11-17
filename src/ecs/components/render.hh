#pragma once
#include "ecs/component.hh"

namespace Parrot {
	// RenderComponent
	class RenderComponent : public Component {
	public:
		// RenderComponent
		RenderComponent(Entity& entity, uuid mesh_uuid, uuid material_uuid);

		// mesh_uuid, material_uuid
		uuid mesh_uuid, material_uuid;
	};
}