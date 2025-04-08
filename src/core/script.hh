#pragma once
#include "event.hh"

namespace Parrot {
  class Script {
  public:
    Script() = default;

    virtual void onUpdate(float32 delta_time);
    virtual bool resolveEvent(const Event& e);
    virtual void raiseEvent(const Event& e) = 0;

    template<class T>
    static usize getID() {
      return typeid(T).hash_code();
    }

    friend Scriptable;
  protected:
    virtual void setScriptOwner(Scriptable* owner) = 0;
  private:
    virtual void onAttach();
    virtual void onDetach();
  };
  template<class T>
  concept ScriptType = std::is_base_of_v<Script, T>;
}