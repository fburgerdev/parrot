#pragma once
#include "common.hh"

namespace Parrot {
  // forward: Scriptable
  class Scriptable;
  // Event
  class Event {
  public:
    // (constructor)
    Event() = default;
    Event(Scriptable* target)
      : target(target) {}

    // getDebugType
    virtual strview getDebugType() const {
      return "Event";
    }

    // target
    Scriptable* target = nullptr;
  };
  // EventResolver
  using EventResolver = Func<bool(const Event&)>;

  // Script
  class Script {
  public:
    // (constructor)
    Script() = default;

    // onUpdate
    virtual void onUpdate(float32 delta_time); /* ASSET_API */
    // resolveEvent
    virtual bool resolveEvent(const Event& e); /* ASSET_API */
    // raiseEvent
    virtual void raiseEvent(const Event& e) = 0; /* ASSET_API */

    // friend: Scriptable
    friend Scriptable;
  protected:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) = 0;
  private:
    // onAttach / onDetach
    virtual void onAttach();
    virtual void onDetach();
  };
  // getScriptID
  template<class T>
  usize getScriptID() {
    return typeid(T).hash_code();
  }
  // ScriptType
  template<class T>
  concept ScriptType = std::is_base_of_v<Script, T>;

  // Scriptable
  class Scriptable {
  public:
    // (constructor)
    Scriptable() = default;
    Scriptable(Scriptable* parent);
    Scriptable(const Scriptable&) = delete;
    Scriptable(Scriptable&&) noexcept;
    // (destructor)
    virtual ~Scriptable();
    // (assignment)
    Scriptable& operator=(const Scriptable&) = delete;
    Scriptable& operator=(Scriptable&& other) noexcept;

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

    // getScript
    template<ScriptType T>
    T& getScript() {
      auto it = _scripts.find(getScriptID<T>());
      // TODO: assert(it != _scripts.end())
      return reinterpret_cast<T&>(*it->second);
    }
    template<ScriptType T>
    const T& getScript() const {
      auto it = _scripts.find(getScriptID<T>());
      // TODO: assert(it != _scripts.end())
      return reinterpret_cast<const T&>(*it->second);
    }
    // addScript
    void addScript(usize uuid, UniquePtr<Script>&& script);
    template<ScriptType T, class... Args>
    T& addScript(Args&&... args) {
      auto result = _scripts.emplace(
        getScriptID<T>(),
        std::make_unique<T>(std::forward<Args>(args)...)
      );
      auto& script = result.first->second;
      // TODO: assert(result.second)
      script->onAttach();
      return reinterpret_cast<T&>(*script);
    }
    // removeScript
    template<ScriptType T>
    void removeScript() {
      auto it = _scripts.find(getScriptID<T>());
      // TODO: assert(it != _scripts.end())
      it->second.onDetach();
      _scripts.erase(it);
    }
    // removeAllScripts
    void removeAllScripts();
    // foreachScript
    void foreachScript(Func<void(Script&)> func);
    void foreachScript(Func<void(const Script&)> func) const;
  private:
    Scriptable* _parent = nullptr;
    HashMap<usize, UniquePtr<Script>> _scripts;
  };
  // makeSingleScriptable
  template<ScriptType T, class... Args>
  Scriptable makeSingleScriptable(Args&&... args) {
    Scriptable out;
    out.addScript<T>(std::forward<Args>(args)...);
    return out;
  }
}