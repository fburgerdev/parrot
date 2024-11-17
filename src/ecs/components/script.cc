#include "common.hh"
#include "script.hh"

namespace Parrot {
	// ScriptComponent
	ScriptComponent::ScriptComponent(Entity& entity, Scene& scene)
		: Component(entity), scene(scene) {}
	// onUpdate
	void ScriptComponent::onUpdate([[maybe_unused]] float32 delta_time) {
		// do nothing
	}
	// onEvent
	bool ScriptComponent::onEvent([[maybe_unused]] const Event& event) {
		return false;
	}
}