#pragma once
#include "registry.hh"
#include "debug/debug.hh"

namespace Parrot {
	// forward: Entity
	class Entity;

	// getComponentID
	template<class T>
	usize getComponentID() {
		return typeid(T).hash_code();
	}
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
	//TODO: replace "derived" with a more descriptive name
	// DerivedComponent
	template<class T>
	class DerivedComponent : public T, public Component {
	public:
		// DerivedComponent / ~DerivedComponent
		DerivedComponent(const T& value, Entity& entity)
			: T(value), Component(entity) {}

		// update
		virtual void update(float32 delta_time) override {
			LOG_ECS_TRACE("update component: {}", static_cast<T&>(*this));
		}
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
	//TODO: replace "derived" with a more descriptive name
	// DerivedComponentConfig
	template<class T>
	class DerivedComponentConfig : public T, public ComponentConfig {
	public:
		// DerivedComponentConfig
		using T::T;

		// getComponentID
		virtual usize getComponentID() const override {
			return typeid(DerivedComponentConfig<T>).hash_code();
		}
		// createComponent
		virtual UniquePtr<Component> createComponent(Entity& entity) const override {
			return std::make_unique<DerivedComponent<T>>(static_cast<const T&>(*this), entity);
		}
	};
}