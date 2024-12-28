#include "common.hh"
#include "entity.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
	// Entity / ~Entity
	Entity::Entity(Scriptable* parent)
		: Scriptable(parent) {}
	Entity::Entity(Entity* parent)
		: Scriptable(parent), _parent(parent) {}
	Entity::Entity(const EntityConfig& config, HandleResolver resolver, Scriptable* parent)
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
			auto [id, factory] = g_registry<Script, Entity&>.at(script_name);
			addScript(id, factory(*this));
		}
	}
	Entity::Entity(const EntityConfig& config, HandleResolver resolver, Entity* parent)
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
			auto [id, factory] = g_registry<Script, Entity&>.at(script_name);
			addScript(id, factory(*this));
		}
	}
	Entity::Entity(uuid id, Entity* parent)
		: UUIDObject(id), _parent(parent) {}
	Entity::~Entity() {
		for (auto& [id, child] : _children) {
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
	void Entity::destroyChild(uuid id) {
		_children.erase(id);
	}
	void Entity::destroyChild(const Entity& child) {
		_children.erase(child.getUUID());
	}
	// :: foreach
	void Entity::foreachChild(function<void(Entity&)> func) {
		for (auto& [id, child] : _children) {
			func(child);
		}
	}
	void Entity::foreachChild(function<void(const Entity&)> func) const {
		for (const auto& [id, child] : _children) {
			func(child);
		}
	}
	// :: foreach (scriptable)
	void Entity::foreachChild(function<void(Scriptable&)> func) {
		for (auto& [id, child] : _children) {
			func(child);
		}
	}
	void Entity::foreachChild(function<void(const Scriptable&)> func) const {
		for (const auto& [id, child] : _children) {
			func(child);
		}
	}

	// update
	void Entity::update(float32 delta_time) {
		LOG_ECS_TRACE("entity update (tag = \"{}\")", _tag);
		for (auto& [id, component] : _components) {
			component->update(delta_time);
		}
		Scriptable::update(delta_time);
		for (auto& [id, child] : _children) {
			child.update(delta_time);
		}
	}
}