#pragma once
#include "ecs/component.hh"

namespace Parrot {
	// forward: Scene, Entity, Event
	class Scene;
	class Entity;
	class Event;

	// ScriptComponent
	class ScriptComponent : public Component {
	public:
		// ScriptComponent
		ScriptComponent(Entity& entity, Scene& scene);

		// onUpdate
		virtual void onUpdate(float32 delta_time);
		// onEvent
		virtual bool onEvent(const Event& event);

		// scene
		Scene& scene;
	};
}