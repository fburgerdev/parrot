#include "common.hh"
#include "entity.hh"
#include "core/log.hh"

namespace Parrot {
  // (constructor)
  Entity::Entity(Scriptable* parent)
    : Scriptable(parent) {}
  Entity::Entity(
    const SharedPtr<EntityPreset>& preset,
    Scriptable* parent, AssetAPI& asset_api
  ) : Scriptable(parent) {
    _tag = preset->tag;
    transform = preset->transform;
    for (const auto& handle : preset->children) {
      auto child = HierarchyNode<Entity>(handle.lock(), this, asset_api);
      _children.emplace(child.getUUID(), std::move(child));
    }
    for (const auto& component_config : preset->components) {
      _components.emplace(
        component_config->getComponentID(),
        component_config->createComponent(*this)
      );
    }
    for (const string& script : preset->scripts) {
      auto [uuid, factory] = g_registry<Script, Entity&, AssetAPI&>.at(script);
      addScript(uuid, factory(*this, asset_api));
    }
  }
  // (destructor)
  Entity::~Entity() {
    for (auto& [uuid, child] : _children) {
      child.removeAllScripts();
    }
    Scriptable::removeAllScripts();
  }

  // getTag
  const string& Entity::getTag() const {
    return _tag;
  }
  // findByTag
  Set<Entity*> Entity::findByTag(
    strview tag, Set<Entity*>&& found
  ) {
    for (auto& [uuid, child] : _children) {
      if (tag == child.getTag()) {
        found.insert(&child);
      }
      if (child.is_visible) {
        found = child.findByTag(tag, std::move(found));
      }
    }
    return found;
  }
  Set<const Entity*> Entity::findByTag(
    strview tag, Set<const Entity*>&& found
  ) const {
    for (const auto& [uuid, child] : _children) {
      if (tag == child.getTag()) {
        found.insert(&child);
      }
      if (child.is_visible) {
        found = child.findByTag(tag, std::move(found));
      }
    }
    return found;
  }

  // child
  // :: create
  Entity& Entity::createChild(bool is_visible) {
    auto child = HierarchyNode<Entity>(this);
    child.is_visible = is_visible;
    return _children.emplace(child.getUUID(), std::move(child)).first->second;
  }
  // :: destroy
  bool Entity::destroyChild(UUID uuid) {
    auto it = _children.find(uuid);
    if (it != _children.end()) {
      if (!it->second.is_static) {
        _children.erase(it);
        return true;
      }
    }
    return false;
  }
  bool Entity::destroyChild(strview tag) {
    bool destroyed = false;
    for (auto it = _children.begin(); it != _children.end();) {
      if (tag == it->second.getTag() && it->second.is_static) {
        it = _children.erase(it);
        destroyed |= true;
      }
      else {
        ++it;
      }
    }
    return destroyed;
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