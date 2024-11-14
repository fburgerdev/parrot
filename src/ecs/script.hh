#pragma once
#include "scene.hh"
#include "entity.hh"

namespace Parrot {
	// forward: Event
	class Event;

	// Script
	class Script {
	public:
		// onUpdate
		virtual void onUpdate(float32 delta_time);
		// onEvent
		virtual bool onEvent(const Event& event);

		// scene, entity
		Scene& scene;
		Entity& entity;
	};
}