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
    T& getScript();
    template<ScriptType T>
    const T& getScript() const;
    // :: add
    void addScript(usize uuid, UniquePtr<Script>&& script);
    template<ScriptType T, class... Args>
    T& addScript(Args&&... args);
    // :: remove
    template<ScriptType T>
    void removeScript();
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
#include "scriptable_impl.hh"