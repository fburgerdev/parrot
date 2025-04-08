#pragma once
#include "core/scriptable.hh"
#include "entity_preset.hh"

namespace Parrot {
  template<class T>
  struct HierarchyNode : public T {
  public:
    using T::T;

    bool is_visible = false;
    bool is_static = false;
  };

  class Entity : public UUIDObject, public Scriptable {
  public:
    Entity(Scriptable* parent = nullptr);
    Entity(
      SharedPtr<const EntityPreset> preset,
      Scriptable* parent, AssetAPI& asset_api
    );
    Entity(const Entity&) = delete;
    Entity(Entity&&) = default;
    ~Entity();
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = default;

    const string& getTag() const;
    Set<Entity*> findByTag(
      strview tag, Set<Entity*>&& found = {}
    );
    Set<const Entity*> findByTag(
      strview tag, Set<const Entity*>&& found = {}
    ) const;

    Entity& createChild(bool is_visible = false);
    bool destroyChild(UUID uuid);
    bool destroyChild(strview tag);
    void foreachChild(Func<void(Entity&)> func);
    void foreachChild(Func<void(const Entity&)> func) const;

    template<class T>
    bool hasComponent() const;
    template<class T>
    T& getComponent();
    template<class T>
    const T& getComponent() const;
    template<class T, class... Args>
    T& addComponent(Args&&... args);
    template<class T>
    void removeComponent();

    void update(float32 delta_time);

    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    Transform<> transform;
  private:
    string _tag;
    Map<UUID, HierarchyNode<Entity>> _children;
    Map<usize, UniquePtr<Component>> _components; //? reduce indirection
  };
}
#include "entity_impl.hh"