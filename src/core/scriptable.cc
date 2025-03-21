#include "common.hh"
#include "scriptable.hh"
#include "log.hh"

namespace Parrot {
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

  // getScriptCount
  usize Scriptable::getScriptCount() const {
    return _scripts.size();
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

  // foreachScript
  void Scriptable::foreachScript(Func<void(Script&)> func) {
    for (auto& [uuid, script] : _scripts) {
      func(*script);
    }
  }
  void Scriptable::foreachScript(Func<void(const Script&)> func) const {
    for (const auto& [uuid, script] : _scripts) {
      func(*script);
    }
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