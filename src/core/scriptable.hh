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
    virtual void onUpdate(float32 delta_time);
    // resolveEvent
    virtual bool resolveEvent(const Event& e);
    // :: capture
    virtual bool resolveEventCapture(const Event& e);
    // :: bubble
    virtual bool resolveEventBubble(const Event& e);
    // :: cascade
    virtual bool resolveEventCascade(const Event& e);

    // raiseEvent
    virtual void raiseEvent(const Event& e) = 0;

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

    // foreachChild
    virtual void foreachChild(Func<void(Scriptable&)> func) = 0;
    virtual void foreachChild(Func<void(const Scriptable&)> func) const = 0;

    // update
    void update(float32 delta_time);

    // resolveEvent
    bool resolveEvent(const Event& e);
    // :: capture
    bool resolveEventCapture(const Event& e);
    // :: bubble
    bool resolveEventBubble(const Event& e);
    // :: cascade
    bool resolveEventCascade(const Event& e);

    // raiseEvent
    void raiseEvent(const Event& e);

    // getScript
    template<class T> requires std::is_base_of_v<Script, T>
    T& getScript() {
      auto it = _scripts.find(getScriptID<T>());
      //TODO: assert(it != _scripts.end())
      return reinterpret_cast<T&>(*it->second);
    }
    template<class T> requires std::is_base_of_v<Script, T>
    const T& getScript() const {
      auto it = _scripts.find(getScriptID<T>());
      //TODO: assert(it != _scripts.end())
      return reinterpret_cast<const T&>(*it->second);
    }
    // addScript
    void addScript(usize uuid, UniquePtr<Script>&& script);
    template<class T, class... Args> requires std::is_base_of_v<Script, T>
    T& addScript(Args&&... args) {
      auto result = _scripts.emplace(
        getScriptID<T>(), std::make_unique<T>(std::forward<Args>(args)...)
      );
      auto& script = result.first->second;
      //TODO: assert(result.second)
      script->onAttach();
      return reinterpret_cast<T&>(*script);
    }
    // removeScript
    template<class T> requires std::is_base_of_v<Script, T>
    void removeScript() {
      auto it = _scripts.find(getScriptID<T>());
      //TODO: assert(it != _scripts.end())
      it->second.onDetach();
      _scripts.erase(it);
    }
    // removeAllScripts
    void removeAllScripts();
  private:
    bool captureEvent(const Event& e);
    bool bubbleEvent(const Event& e);
    bool cascadeEvent(const Event& e);

    Scriptable* _parent = nullptr;
    HashMap<usize, UniquePtr<Script>> _scripts;
  };
  // makeSingleScriptable
  template<class T, class... Args> requires std::is_base_of_v<Script, T>
  Scriptable makeSingleScriptable(Args&&... args) {
    Scriptable out;
    out.addScript<T>(std::forward<Args>(args)...);
    return out;
  }
}