#pragma once
#include "script.hh"

namespace Parrot {
  // Scriptable
  class Scriptable {
  public:
    // (constructor)
    Scriptable() = default;
    Scriptable(Scriptable* parent);
    Scriptable(const Scriptable&) = delete;
    Scriptable(Scriptable&&) noexcept;
    // (assignment)
    Scriptable& operator=(const Scriptable&) = delete;
    Scriptable& operator=(Scriptable&& other) noexcept;
    // (destructor)
    virtual ~Scriptable();

    // foreachChild (interface)
    virtual void foreachChild(Func<void(Scriptable&)> func) = 0;
    virtual void foreachChild(Func<void(const Scriptable&)> func) const = 0;

    // update
    void update(float32 delta_time);
    // raiseEvent
    void raiseEvent(const Event& e);
    // cascadeEvent
    void cascadeEvent(const Event& e);
    // resolveEvent
    bool resolveEvent(const Event& e);

    // script
    // :: count
    usize getScriptCount() const;
    // :: get
    template<ScriptType T>
    T& getScript() {
      auto it = _scripts.find(Script::getID<T>());
      // TODO: assert(it != _scripts.end())
      return reinterpret_cast<T&>(*it->second);
    }
    template<ScriptType T>
    const T& getScript() const {
      auto it = _scripts.find(Script::getID<T>());
      // TODO: assert(it != _scripts.end())
      return reinterpret_cast<const T&>(*it->second);
    }
    // :: add
    void addScript(usize uuid, UniquePtr<Script>&& script);
    template<ScriptType T, class... Args>
    T& addScript(Args&&... args) {
      auto result = _scripts.emplace(
        Script::getID<T>(),
        std::make_unique<T>(std::forward<Args>(args)...)
      );
      auto& script = result.first->second;
      // TODO: assert(result.second)
      script->onAttach();
      return reinterpret_cast<T&>(*script);
    }
    // :: remove
    template<ScriptType T>
    void removeScript() {
      auto it = _scripts.find(Script::getID<T>());
      // TODO: assert(it != _scripts.end())
      it->second->onDetach();
      _scripts.erase(it);
    }
    // :: remove-all
    void removeAllScripts();
    // :: foreach
    void foreachScript(Func<void(Script&)> func);
    void foreachScript(Func<void(const Script&)> func) const;
  private:
    Scriptable* _parent = nullptr;
    HashMap<usize, UniquePtr<Script>> _scripts;
  };
}