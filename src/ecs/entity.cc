#include "common.hh"
#include "entity.hh"
#include "debug/debug.hh"

namespace Parrot {
	// Entity
	Entity::Entity(uuid uuid, Entity* parent)
		: UUIDObject(uuid), _parent(parent) {}

	// hasParent
	bool Entity::hasParent() const {
		return _parent;
	}
	// getParent
	Entity& Entity::getParent() {
		return *_parent;
	}
	const Entity& Entity::getParent() const {
		return *_parent;
	}

	// createChild
	Entity& Entity::createChild() {
		uuid uuid = generateUUID();
		_children.emplace(uuid, Entity(uuid, this));
		return _children.at(uuid);
	}
	Entity& Entity::createChild(stdf::path& filepath) {
		// TODO
		return *this;
	}
	// destroyChild
	void Entity::destroyChild(uuid uuid) {
		_children.erase(uuid);
	}
	void Entity::destroyChild(const Entity& child) {
		_children.erase(child.getUUID());
	}
	// foreachChild
	void Entity::foreachChild(function<void(Entity&)> func) {
		for (auto& [uuid, child] : _children) {
			func(child);
		}
	}
	void Entity::foreachChild(function<void(const Entity&)> func) const {
		for (const auto& [uuid, child] : _children) {
			func(child);
		}
	}

	// update
	void Entity::update(float32 delta_time) {
		LOG_ECS_TRACE("entity update (tag = \"{}\")", _tag);
		for (auto& [id, component] : _components) {
			component->update(delta_time);
		}
		for (auto& [uuid, child] : _children) {
			child.update(delta_time);
		}
	}
}