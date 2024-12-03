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
	Scriptable::Scriptable(Scriptable* parent)
		: _parent(parent) {}
	Scriptable::~Scriptable() {
		for (auto& [id, script] : _scripts) {
			script->onDetach();
		}
	}

	// raiseEvent
	void Scriptable::raiseEvent(const Event& e) {
		if (captureEvent(e)) {
			return;
		}
		else if (resolveEvent(e)) {
			return;
		}
		else {
			if (!bubbleEvent(e)) {
				LOG_CORE_TRACE("unresolved event"); //TODO: print event
			}
		}
	}
	// captureEvent
	bool Scriptable::captureEvent(const Event& e) {
		if (_parent == nullptr) {
			return resolveEvent(e);
		}
		return _parent->captureEvent(e) || resolveEvent(e);
	}
	// resolveEvent
	bool Scriptable::resolveEvent(const Event& e) {
		bool resolved = false;
		for (auto& [id, script] : _scripts) {
			resolved |= script->resolveEvent(e);
		}
		return resolved;
	}
	// bubbleEvent
	bool Scriptable::bubbleEvent(const Event& e) {
		if (resolveEvent(e)) {
			return true;
		}
		else if (_parent) {
			return _parent->bubbleEvent(e);
		}
		return false;
	}
}