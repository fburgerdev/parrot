#pragma once

namespace Parrot {
  // script
  // :: get
  template<ScriptType T>
  T& Scriptable::getScript() {
    auto it = _scripts.find(Script::getID<T>());
    /* TODO: assert(it != _scripts.end()) */
    return reinterpret_cast<T&>(*it->second);
  }
  template<ScriptType T>
  const T& Scriptable::getScript() const {
    auto it = _scripts.find(Script::getID<T>());
    /* TODO: assert(it != _scripts.end()) */
    return reinterpret_cast<const T&>(*it->second);
  }
  // :: add
  template<ScriptType T, class... Args>
  T& Scriptable::addScript(Args&&... args) {
    auto result = _scripts.emplace(
      Script::getID<T>(),
      std::make_unique<T>(std::forward<Args>(args)...)
    );
    auto& script = result.first->second;
    /* TODO: assert(result.second) */
    script->onAttach();
    return reinterpret_cast<T&>(*script);
  }
  // :: remove
  template<ScriptType T>
  void Scriptable::removeScript() {
    auto it = _scripts.find(Script::getID<T>());
    /* TODO: assert(it != _scripts.end()) */
    it->second->onDetach();
    _scripts.erase(it);
  }
}