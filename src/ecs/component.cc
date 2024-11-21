#include "common.hh"
#include "component.hh"
#include "debug/debug.hh"

namespace Parrot {
	// Component
	Component::Component(Entity& entity)
		: entity(entity) {}
	// ~Component
	Component::~Component() {
		// do nothing
	}
	// update
	void Component::update([[maybe_unused]] float32 update) {
		LOG_ECS_TRACE("component update");
	}
}