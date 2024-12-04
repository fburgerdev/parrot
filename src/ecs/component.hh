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
		virtual ~Component() = default;
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

	// DerivedComponent
	template<class T>
	class DerivedComponent : public T, public Component {
	public:
		// DerivedComponent / ~DerivedComponent
		DerivedComponent(const T& value, Entity& entity)
			: T(value), Component(entity) {}
		virtual ~DerivedComponent() = default;
	};
	// ComponentConfig
	class ComponentConfig {
	public:
		// ~ComponentConfig
		virtual ~ComponentConfig() = default;

		// getComponentID
		virtual usize getComponentID() const = 0;
		// createComponent
		virtual UniquePtr<Component> createComponent(Entity& entity) const = 0;
	};
}