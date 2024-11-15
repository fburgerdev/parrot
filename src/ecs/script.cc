#include "common.hh"
#include "script.hh"

namespace Parrot {
	// onUpdate
	void Script::onUpdate([[maybe_unused]] float32 delta_time) {
		// do nothing
	}
	// onEvent
	bool Script::onEvent([[maybe_unused]] const Event& event) {
		return false;
	}
}