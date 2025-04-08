#pragma once
#include "script.hh"

namespace Parrot {
  class Scriptable {
  public:
    Scriptable() = default;
    Scriptable(Scriptable* parent);
    Scriptable(const Scriptable&) = delete;
    Scriptable(Scriptable&&) noexcept;
    Scriptable& operator=(const Scriptable&) = delete;
    Scriptable& operator=(Scriptable&& other) noexcept;
    virtual ~Scriptable();

    virtual void foreachChild(Func<void(Scriptable&)> func) = 0;
    virtual void foreachChild(Func<void(const Scriptable&)> func) const = 0;

    void update(float32 delta_time);
    void raiseEvent(const Event& e);
    void cascadeEvent(const Event& e);
    bool resolveEvent(const Event& e);

    usize getScriptCount() const;
    template<ScriptType T>
    T& getScript();
    template<ScriptType T>
    const T& getScript() const;
    void addScript(usize uuid, UniquePtr<Script>&& script);
    template<ScriptType T, class... Args>
    T& addScript(Args&&... args);
    template<ScriptType T>
    void removeScript();
    void removeAllScripts();
    void foreachScript(Func<void(Script&)> func);
    void foreachScript(Func<void(const Script&)> func) const;
  private:
    Scriptable* _parent = nullptr;
    HashMap<usize, UniquePtr<Script>> _scripts;
  };
}
#include "scriptable_impl.hh"