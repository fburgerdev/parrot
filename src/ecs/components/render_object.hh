#pragma once
#include "ecs/component.hh"

namespace Parrot {
	// RenderObject
	struct RenderObject : public ComponentConfig {
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

		// getComponentID
		virtual usize getComponentID() const override;
		// createComponent
		virtual UniquePtr<Component> createComponent(Entity& entity) const override;

		// mesh_uuid, material_uuid
		uuid mesh_uuid = 0, material_uuid = 0;
	};

	// RenderObjectComponent
	class RenderObjectComponent : public DerivedComponent<RenderObject> {
	public:
		// RenderObjectComponent
		using DerivedComponent<RenderObject>::DerivedComponent;

		// update
		virtual void update(float32 delta_time) override;
	};

	// <<
	ostream& operator<<(ostream& stream, const RenderObject& render_object);
}