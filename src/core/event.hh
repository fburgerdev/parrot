#pragma once
#include "common.hh"

namespace Parrot {
  class Scriptable;
  /// @brief Base class event types.
  class Event {
  public:
    /// @brief Construct an empty Event (with no target).
    Event() = default;
    /// @param target The origin of the Event
    /// @todo turn pointer into reference
    Event(Scriptable* target);

    /// @return Type of event
    /// (@c "Event" if not overwritten by derived classes).
    virtual strview getDebugType() const;

    /// @brief Where the Event originates
    Scriptable* target = nullptr;
  };
  using EventResolver = Func<bool(const Event&)>;
}