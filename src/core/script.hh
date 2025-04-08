#pragma once
#include "event.hh"

namespace Parrot {
  /// @brief Base class for script types.
  class Script {
  public:
    Script() = default;

    /// @brief Method that is invoked every time the game is updated.
    /// @note Unless overwritten, this method does nothing.
    virtual void onUpdate(float32 delta_time);
    /// @return Whether the Event could be resolved
    /// @note Unless overwritten, this method does nothing and returns @c false.
    virtual bool resolveEvent(const Event& e);
    virtual void raiseEvent(const Event& e) = 0;

    template<class T>
    static usize getID();

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
#include "script_impl.hh"