#pragma once

namespace Parrot {
  // component
  // :: has
  template<class T>
  bool Entity::hasComponent() const {
    return _components.contains(typeid(T).hash_code());
  }
  // :: get
  template<class T>
  T& Entity::getComponent() {
    return dynamic_cast<T&>(*_components.at(typeid(T).hash_code()));
  }
  template<class T>
  const T& Entity::getComponent() const {
    return dynamic_cast<const T&>(*_components.at(typeid(T).hash_code()));
  }
  // :: add
  template<class T, class... Args>
  T& Entity::addComponent(Args&&... args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    _components.emplace(typeid(T).hash_code(), std::move(component));
    return getComponent<T>();
  }
  // :: remove
  template<class T>
  void Entity::removeComponent() {
    _components.erase(typeid(T).hash_code());
  }
}