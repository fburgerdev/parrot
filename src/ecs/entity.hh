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
      const SharedPtr<EntityPreset>& preset,
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
    const string& getTag() const; /* PARROT_API */
    // findByTag
    Set<Entity*> findByTag(
      strview tag, Set<Entity*>&& found = {}
    ); /* PARROT_API */
    Set<const Entity*> findByTag(
      strview tag, Set<const Entity*>&& found = {}
    ) const; /* PARROT_API */

    // children
    // :: create
    Entity& createChild(bool is_visible = false); /* PARROT_API */
    // :: destroy
    bool destroyChild(UUID uuid); /* PARROT_API */
    bool destroyChild(strview tag); /* PARROT_API */
    // :: foreach
    void foreachChild(Func<void(Entity&)> func); /* PARROT_API */
    void foreachChild(Func<void(const Entity&)> func) const; /* PARROT_API */

    // component
    // :: has
    template<class T>
    bool hasComponent() const /* PARROT_API */ {
      return _components.contains(getComponentID<T>());
    }
    // :: get
    template<class T>
    T& getComponent() /* PARROT_API */ {
      return dynamic_cast<T&>(*_components.at(getComponentID<T>()));
    }
    template<class T>
    const T& getComponent() const /* PARROT_API */ {
      return dynamic_cast<const T&>(*_components.at(getComponentID<T>()));
    }
    // :: add
    template<class T, class... TArgs>
    T& addComponent(TArgs&&... args) /* PARROT_API */ {
      _components.emplace(
        getComponentID<T>(),
        std::make_unique<T>(*this, std::forward<TArgs>(args)...)
      );
      return getComponent<T>();
    }
    // :: remove
    template<class T>
    void removeComponent() /* PARROT_API */ {
      _components.erase(getComponentID<T>());
    }

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
    Transform<> transform; /* PARROT_API */
  private:
    string _tag;
    Map<UUID, HierarchyNode<Entity>> _children;
    Map<usize, UniquePtr<Component>> _components; //? reduce indirection
  };
}