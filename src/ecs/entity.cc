#include "common.hh"
#include "entity.hh"

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
}