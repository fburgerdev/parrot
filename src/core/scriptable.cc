#include "common.hh"
#include "scriptable.hh"
#include "log.hh"

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

  //* Scriptable
  // (constructor)
  Scriptable::Scriptable(Scriptable* parent)
    : _parent(parent) {}
  Scriptable::Scriptable(Scriptable&& other) noexcept
    : _parent(std::exchange(other._parent, nullptr)),
      _scripts(std::move(other._scripts)) {
    for (auto& [id, script] : _scripts) {
      script->setScriptOwner(this);
    }
  }
  // (destructor)
  Scriptable::~Scriptable() {
    // TODO: assert all detached
  }
  // (assignment)
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
    if (!resolveEvent(e) && _parent) {
      _parent->raiseEvent(e);
    }
  }
  // cascadeEvent
  void Scriptable::cascadeEvent(const Event& e) {
    foreachChild([&](Scriptable& child) {
      child.resolveEvent(e);
      child.cascadeEvent(e);
    });
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