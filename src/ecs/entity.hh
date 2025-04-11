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

  /// @ingroup PublicAPI
  /// @brief Hierarchical object composed by Components.
  class Entity : public UUIDObject, public Scriptable {
  public:
    /// @brief Construct an Entity with no components or scripts attached.
    /// @param parent Parent Scriptable used for propagating events
    Entity(Scriptable* parent = nullptr);
    /// @brief Construct an Entity based on an EntityPreset.
    /// @param preset EntityPreset the Entity is based on
    /// @param parent Parent Scriptable used for propagating events
    /// @param asset_api For usage by the client in attached EntityScripts
    Entity(
      SharedPtr<const EntityPreset> preset,
      Scriptable* parent, AssetAPI& asset_api
    );
    /// @note Copying attached Components is not implemented
    Entity(const Entity&) = delete;
    /// @note Explict move because of explicit copy delete
    Entity(Entity&&) = default;
    /// @note Manually remove all attached Scripts
    ~Entity();
    /// @note Copying attached Components is not implemented
    Entity& operator=(const Entity&) = delete;
    /// @note Explict move because of explicit copy delete
    Entity& operator=(Entity&&) = default;

    /// @brief Access tag of the Entity.
    /// @return The tag of the Entity.
    const string& getTag() const;
    /// @brief Find all (recursive) children with a certain tag.
    /// @param tag The tag to be searched for
    /// @param found Children already found
    /// @return A Set with pointers to all found children 
    Set<Entity*> findByTag(
      strview tag, Set<Entity*>&& found = {}
    );
    /// @brief Find all (recursive) children with a certain tag.
    /// @param tag The tag to be searched for
    /// @param found Children already found
    /// @return A Set with pointers to all found children 
    Set<const Entity*> findByTag(
      strview tag, Set<const Entity*>&& found = {}
    ) const;

    /// @brief Create a child Entity.
    /// @param is_visible Whether the child Entity is visible,
    /// i.e. whether it can be accessed by non-immediate parents
    /// @return Reference to the created child Entity
    Entity& createChild(bool is_visible = false);
    /// @brief Destroy child Entity with the UUID @c uuid.
    /// @param uuid The UUID of the child Entity
    /// @return Whether a child Entity with UUID @c uuid existed
    bool destroyChild(UUID uuid);
    /// @brief Destroy child Entity with the tag @c tag.
    /// @param tag The tag of the child Entity
    /// @return Whether a child Entity with the tag @c tag existed
    bool destroyChild(strview tag);
    /// @brief Iterate over every child Entity.
    /// @param func Callback function called for every child Entity
    void foreachChild(Func<void(Entity&)> func);
    /// @brief Iterate over every child Entity.
    /// @param func Callback function called for every child Entity
    void foreachChild(Func<void(const Entity&)> func) const;

    /// @tparam T Component type
    /// @return Whether the Entity holds a Component of type @c T
    template<class T>
    bool hasComponent() const;
    /// @brief Access existing Component of type @c T hold by the Entity.
    /// @tparam T Component type 
    /// @return Reference to the Component of type @c T hold by the Entity
    template<class T>
    T& getComponent();
    /// @brief Access existing Component of type @c T hold by the Entity.
    /// @tparam T Component type 
    /// @return Reference to the Component of type @c T hold by the Entity
    template<class T>
    const T& getComponent() const;
    /// @brief Emplace Component of type @c T.
    /// @tparam T Component type 
    /// @return Reference to the constructed Component
    template<class T, class... Args>
    T& addComponent(Args&&... args);
    /// @brief Remove Component of type @c T from Entity.
    /// @tparam T Component type 
    template<class T>
    void removeComponent();

    /// @brief Update all child Entities, Components and Scripts attached
    /// @param delta_time Seconds elapsed since last update
    void update(float32 delta_time);

    /// @brief Iterate overy every child Entity as Scriptable.
    /// @param func Callback function called for every child Scriptable
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    /// @brief Iterate overy every child Entity as Scriptable.
    /// @param func Callback function called for every child Scriptable
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    /// @brief Position, rotation and scale of the Entity.
    Transform<> transform;
  private:
    string _tag;
    Map<UUID, HierarchyNode<Entity>> _children;
    Map<usize, UniquePtr<Component>> _components; //? reduce indirection
  };
}
#include "entity_impl.hh"