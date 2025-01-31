#include "common.hh"
#include "component.hh"

namespace Parrot {
	// (constructor)
	Component::Component(Entity& entity)
		: entity(entity) {}
	// update
	void Component::update([[maybe_unused]] float32 update) {
		LOG_ECS_TRACE("component update");
	}
}