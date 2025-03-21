#pragma once
#include "event.hh"

namespace Parrot {
  // Script
  class Script {
  public:
    // (constructor)
    Script() = default;

    // onUpdate
    virtual void onUpdate(float32 delta_time); /* API */
    // resolveEvent
    virtual bool resolveEvent(const Event& e); /* API */
    // raiseEvent
    virtual void raiseEvent(const Event& e) = 0; /* API */

    // getID
    template<class T>
    static usize getID() {
      return typeid(T).hash_code();
    }

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
  // ScriptType
  template<class T>
  concept ScriptType = std::is_base_of_v<Script, T>;
}