#pragma once
#include "debug/engine_logger.hh"

namespace Parrot {
  // getComponentID
  template<class T>
  usize getComponentID() {
    return typeid(T).hash_code();
  }

  // forward: Entity
  class Entity;
  // Component
  class Component {
  public:
    // (constructor)
    Component(Entity& entity);
    // (destructor)
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
    // (constructor)
    DerivedComponent(const T& value, Entity& entity)
      : T(value), Component(entity) {}
    // update
    virtual void update([[maybe_unused]] float32 delta_time) override {
      LOG_ECS_TRACE("update component: {}", static_cast<T&>(*this));
    }
  };

  // ComponentConfig
  class ComponentConfig {
  public:
    // (destructor)
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
    // (constructor)
    using T::T;
    // getComponentID
    virtual usize getComponentID() const override {
      return Parrot::getComponentID<DerivedComponent<T>>();
    }
    // createComponent
    virtual UniquePtr<Component> createComponent(Entity& entity) const override {
      return std::make_unique<DerivedComponent<T>>(static_cast<const T&>(*this), entity);
    }
  };
}