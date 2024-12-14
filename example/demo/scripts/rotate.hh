#pragma once
#include "client.hh"

namespace Parrot {
	// Rotate
	class Rotate : public EntityScript {
	public:
		// Rotate
		Rotate(Entity& entity)
			: EntityScript(entity) {}

		// onUpdate
		virtual void onUpdate(float32 delta_time) override {
			entity->transform.rotation.x += 0.5F * delta_time;
			entity->transform.rotation.y += 0.5F * delta_time;
		}
	};
}