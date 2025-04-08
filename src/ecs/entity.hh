#pragma once
#include "core/scriptable.hh"
#include "entity_preset.hh"

namespace Parrot {
  // HierarchyNode
  template<class T>
  struct HierarchyNode : public T {
  public:
    // (constructor)
    using T::T;

    // is_visible, is_static
    bool is_visible = false;
    bool is_static = false;
  };

  // Entity
  class Entity : public UUIDObject, public Scriptable {
  public:
    // (constructor)
    Entity(Scriptable* parent = nullptr);
    Entity(
      SharedPtr<const EntityPreset> preset,
      Scriptable* parent, AssetAPI& asset_api
    );
    Entity(const Entity&) = delete;
    Entity(Entity&&) = default;
    // (destructor)
    ~Entity();
    // (assignment)
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = default;

    // getTag
    const string& getTag() const;
    // findByTag
    Set<Entity*> findByTag(
      strview tag, Set<Entity*>&& found = {}
    );
    Set<const Entity*> findByTag(
      strview tag, Set<const Entity*>&& found = {}
    ) const;

    // children
    // :: create
    Entity& createChild(bool is_visible = false);
    // :: destroy
    bool destroyChild(UUID uuid);
    bool destroyChild(strview tag);
    // :: foreach
    void foreachChild(Func<void(Entity&)> func);
    void foreachChild(Func<void(const Entity&)> func) const;

    // component
    // :: has
    template<class T>
    bool hasComponent() const;
    // :: get
    template<class T>
    T& getComponent();
    template<class T>
    const T& getComponent() const;
    // :: add
    template<class T, class... Args>
    T& addComponent(Args&&... args);
    // :: remove
    template<class T>
    void removeComponent();

    // update
    void update(float32 delta_time);

    // foreachChild (impl. Scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    // transform
    Transform<> transform;
  private:
    string _tag;
    Map<UUID, HierarchyNode<Entity>> _children;
    Map<usize, UniquePtr<Component>> _components; //? reduce indirection
  };

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