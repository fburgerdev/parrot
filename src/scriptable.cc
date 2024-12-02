#include "common.hh"
#include "scriptable.hh"
#include "debug/debug.hh"

namespace Parrot {
	// onAttach / onDetach
	void Script::onAttach() {
		LOG_CORE_TRACE("Script::onAttach");
	}
	void Script::onDetach() {
		LOG_CORE_TRACE("Script::onDetach");
	}
	// onUpdate
	void Script::onUpdate([[maybe_unused]] float32 delta_time) {
		LOG_CORE_TRACE("Script::onUpdate(delta_time={})", delta_time);
	}
	// resolveEvent
	bool Script::resolveEvent([[maybe_unused]] const Event& e) {
		return false;
	}

	// Scriptable / ~Scriptable
	Scriptable::Scriptable(EventResolver capture, EventResolver bubble)
		: _capture(capture), _bubble(bubble) {}
	Scriptable::~Scriptable() {
		for (auto& [id, script] : _scripts) {
			script->onDetach();
		}
	}

	// getCaptureCallback / getBubbleCallback
	const EventResolver& Scriptable::getCaptureCallback() {
		return _capture;
	}
	const EventResolver& Scriptable::getBubbleCallback() {
		return _bubble;
	}
	// raiseEvent
	void Scriptable::raiseEvent(const Event& e) {
		if (_capture(e)) {
			return;
		}
		else if (resolveEvent(e)) {
			return;
		}
		else {
			if (!_bubble(e)) {
				LOG_CORE_DEBUG("unresolved event"); //TODO: print event
			}
		}
	}
	// resolveEvent
	bool Scriptable::resolveEvent(const Event& e) {
		bool resolved = false;
		for (auto& [id, script] : _scripts) {
			resolved |= script->resolveEvent(e);
		}
		return resolved;
	}
}