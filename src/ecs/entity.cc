#include "common.hh"
#include "entity.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
	// Entity / ~Entity
	Entity::Entity(Scriptable* parent)
		: Scriptable(parent) {}
	Entity::Entity(Entity* parent)
		: Scriptable(parent), _parent(parent) {}
	Entity::Entity(const EntityConfig& config, AssetHandleResolver resolver, Scriptable* parent)
		: Scriptable(parent) {
		_tag = config.tag;
		transform = config.transform;
		for (const auto& handle : config.children) {
			resolver.useHandle<EntityConfig>([&](const EntityConfig& config) {
				Entity child = Entity(config, resolver, this);
				_children.emplace(child.getUUID(), std::move(child));
			}, handle);
		}
		for (const auto& component_config : config.components) {
			_components.emplace(
				component_config->getComponentID(),
				component_config->createComponent(*this)
			);
		}
		for (const string& script_name : config.scripts) {
			auto [uuid, factory] = g_registry<Script, Entity&>.at(script_name);
			addScript(uuid, factory(*this));
		}
	}
	Entity::Entity(const EntityConfig& config, AssetHandleResolver resolver, Entity* parent)
		: Scriptable(parent), _parent(parent) {
		_tag = config.tag;
		transform = config.transform;
		for (const auto& handle : config.children) {
			resolver.useHandle<EntityConfig>([&](const EntityConfig& config) {
				Entity child = Entity(config, resolver, this);
				_children.emplace(child.getUUID(), std::move(child));
			}, handle);
		}
		for (const auto& component_config : config.components) {
			_components.emplace(
				component_config->getComponentID(),
				component_config->createComponent(*this)
			);
		}
		for (const string& script_name : config.scripts) {
			auto [uuid, factory] = g_registry<Script, Entity&>.at(script_name);
			addScript(uuid, factory(*this));
		}
	}
	Entity::Entity(UUID uuid, Entity* parent)
		: UUIDObject(uuid), _parent(parent) {}
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