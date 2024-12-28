#include "common.hh"
#include "core/scriptable.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
	//* Script
	// onAttach / onDetach
	void Script::onAttach() {
		LOG_APP_TRACE("Script::onAttach");
	}
	void Script::onDetach() {
		LOG_APP_TRACE("Script::onDetach");
	}
	
	// onUpdate
	void Script::onUpdate([[maybe_unused]] float32 delta_time) {
		LOG_APP_TRACE("Script::onUpdate(delta_time={})", delta_time);
	}

	// resolveEvent
	bool Script::resolveEvent([[maybe_unused]] const Event& e) {
		return false;
	}
	// :: capture
	bool Script::resolveEventCapture([[maybe_unused]] const Event& e) {
		return false;
	}
	// :: bubble
	bool Script::resolveEventBubble([[maybe_unused]] const Event& e) {
		return false;
	}
	// :: cascade
	bool Script::resolveEventCascade([[maybe_unused]] const Event& e) {
		return false;
	}

	//* Scriptable
	// Scriptable / ~Scriptable
	Scriptable::Scriptable(Scriptable* parent)
		: _parent(parent) {}
	Scriptable::Scriptable(Scriptable&& other) noexcept
		: _parent(std::exchange(other._parent, nullptr)),
		  _scripts(std::move(other._scripts)) {
		for (auto& [id, script] : _scripts) {
			script->setScriptOwner(this);
		}
	}
	Scriptable::~Scriptable() {
		//TODO: assert all detached
	}
	// =
	Scriptable& Scriptable::operator=(Scriptable&& other) noexcept {
		_parent = std::exchange(other._parent, nullptr);
		_scripts = std::move(other._scripts);
		for (auto& [id, script] : _scripts) {
			script->setScriptOwner(this);
		}
		return *this;
	}

	// addScript
	void Scriptable::addScript(usize id, UniquePtr<Script>&& script) {
		_scripts.emplace(id, std::move(script)).first->second->onAttach();
	}
	// removeAllScripts
	void Scriptable::removeAllScripts() {
		for (auto& [id, script] : _scripts) {
			script->onDetach();
		}
		_scripts.clear();
	}

	// update
	void Scriptable::update(float32 delta_time) {
		for (auto& [id, script] : _scripts) {
			script->onUpdate(delta_time);
		}
	}

	// raiseEvent
	void Scriptable::raiseEvent(const Event& e) {
		captureEvent(e) || bubbleEvent(e) || cascadeEvent(e);
	}

	// resolveEvent
	bool Scriptable::resolveEvent(const Event& e) {
		bool resolved = false;
		for (auto& [id, script] : _scripts) {
			resolved |= script->resolveEvent(e);
		}
		return resolved;
	}
	// :: capture
	bool Scriptable::resolveEventCapture(const Event& e) {
		bool resolved = false;
		for (auto& [id, script] : _scripts) {
			resolved |= script->resolveEventCapture(e) | script->resolveEvent(e);
		}
		return resolved;
	}
	// :: bubble
	bool Scriptable::resolveEventBubble(const Event& e) {
		bool resolved = false;
		for (auto& [id, script] : _scripts) {
			resolved |= script->resolveEventBubble(e) | script->resolveEvent(e);
		}
		return resolved;
	}
	// :: cascade
	bool Scriptable::resolveEventCascade(const Event& e) {
		bool resolved = false;
		for (auto& [id, script] : _scripts) {
			resolved |= script->resolveEventCascade(e) | script->resolveEvent(e);
		}
		return resolved;
	}

	// captureEvent
	bool Scriptable::captureEvent(const Event& e) {
		if (_parent == nullptr) {
			return resolveEventCapture(e);
		}
		return _parent->captureEvent(e) || resolveEventCapture(e);
	}
	// bubbleEvent
	bool Scriptable::bubbleEvent(const Event& e) {
		return resolveEventBubble(e) || (_parent ? _parent->bubbleEvent(e) : false);
	}
	// cascadeEvent
	bool Scriptable::cascadeEvent(const Event& e) {
		bool resolved = true;
		foreachChild([&](Scriptable& child) {
			resolved |= child.cascadeEvent(e);
		});
		return resolved;
	}
}