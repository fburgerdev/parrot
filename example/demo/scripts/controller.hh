#pragma once
#include "client.hh"

namespace Parrot {
	// PlayerController
	class PlayerController : public Script {
	public:
		// PlayerController
		PlayerController(Entity& entity)
			: entity(entity) {}

		// onUpdate
		virtual void onUpdate(float32 delta_time) override {
			// controls...
		}

		// entity
		Entity& entity;
	};
}