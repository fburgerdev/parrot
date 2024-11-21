#pragma once
#include "uuid.hh"

namespace Parrot {
	// forward: Entity
	class Entity;

	// Component
	class Component {
	public:
		// Component
		Component(Entity& entity);
		// ~Component
		virtual ~Component();
		// update
		virtual void update(float32 update);

		// entity
		Entity& entity;
	};
	// getComponentID
	template<class T>
	usize getComponentID() {
		return typeid(T).hash_code();
	}
}