#include "common.hh"
#include "entity.hh"
#include "core/log.hh"

namespace Parrot {
  // (constructor)
  Entity::Entity(Scriptable* parent)
    : Scriptable(parent) {}
  Entity::Entity(Entity* parent)
    : Scriptable(parent), _parent(parent) {}
  Entity::Entity(
    const SharedPtr<EntityPreset>& preset,
    Scriptable* parent, AssetAPI& asset_api
  ) : Scriptable(parent) {
    _tag = preset->tag;
    transform = preset->transform;
    for (const auto& handle : preset->children) {
      Entity child = Entity(handle.lock(), this, asset_api);
      _children.emplace(child.getUUID(), std::move(child));
    }
    for (const auto& component_config : preset->components) {
      _components.emplace(
        component_config->getComponentID(),
        component_config->createComponent(*this)
      );
    }
    for (const string& script_name : preset->scripts) {
      auto [uuid, factory] = g_registry<Script, Entity&, AssetAPI&>.at(
        script_name
      );
      addScript(uuid, factory(*this, asset_api));
    }
  }
  Entity::Entity(
    const SharedPtr<EntityPreset>& preset,
    Entity* parent, AssetAPI& asset_api
  ) : Scriptable(parent), _parent(parent) {
    _tag = preset->tag;
    transform = preset->transform;
    for (const auto& handle : preset->children) {
      Entity child = Entity(handle.lock(), this, asset_api);
      _children.emplace(child.getUUID(), std::move(child));
    }
    for (const auto& component_config : preset->components) {
      _components.emplace(
        component_config->getComponentID(),
        component_config->createComponent(*this)
      );
    }
    for (const string& script_name : preset->scripts) {
      auto [uuid, factory] = g_registry<Script, Entity&, AssetAPI&>.at(
        script_name
      );
      addScript(uuid, factory(*this, asset_api));
    }
  }
  Entity::Entity(UUID uuid, Entity* parent)
    : UUIDObject(uuid), _parent(parent) {}
  // (destructor)
  Entity::~Entity() {
    for (auto& [uuid, child] : _children) {
      child.removeAllScripts();
    }
    Scriptable::removeAllScripts();
  }

  // parent
  // :: has
  bool Entity::hasParent() const {
    return _parent;
  }
  // :: get
  Entity& Entity::getParent() {
    return *_parent;
  }
  const Entity& Entity::getParent() const {
    return *_parent;
  }

  // child
  // :: create
  Entity& Entity::createChild() {
    Entity child(this);
    return _children.emplace(child.getUUID(), std::move(child)).first->second;
  }
  // :: destroy
  void Entity::destroyChild(UUID uuid) {
    _children.erase(uuid);
  }
  void Entity::destroyChild(const Entity& child) {
    _children.erase(child.getUUID());
  }
  // :: foreach
  void Entity::foreachChild(Func<void(Entity&)> func) {
    for (auto& [uuid, child] : _children) {
      func(child);
    }
  }
  void Entity::foreachChild(Func<void(const Entity&)> func) const {
    for (const auto& [uuid, child] : _children) {
      func(child);
    }
  }
  // :: foreach (scriptable)
  void Entity::foreachChild(Func<void(Scriptable&)> func) {
    for (auto& [uuid, child] : _children) {
      func(child);
    }
  }
  void Entity::foreachChild(Func<void(const Scriptable&)> func) const {
    for (const auto& [uuid, child] : _children) {
      func(child);
    }
  }

  // update
  void Entity::update(float32 delta_time) {
    LOG_ECS_TRACE("entity update (tag = \"{}\")", _tag);
    for (auto& [uuid, component] : _components) {
      component->update(delta_time);
    }
    Scriptable::update(delta_time);
    for (auto& [uuid, child] : _children) {
      child.update(delta_time);
    }
  }
}