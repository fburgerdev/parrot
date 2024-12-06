#pragma once
#include "client.hh"

namespace Parrot {
	// Rotate
	class Rotate : public Script {
	public:
		// Rotate
		Rotate(Entity& entity)
			: entity(entity) {}

		// onUpdate
		virtual void onUpdate(float32 delta_time) override {
			entity.transform.rotation.y += 0.5F * delta_time;
		}

		// entity
		Entity& entity;
	};
}