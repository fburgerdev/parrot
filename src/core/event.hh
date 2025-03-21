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
    Event(Scriptable* target);

    // getDebugType
    virtual strview getDebugType() const;

    // target
    Scriptable* target = nullptr;
  };
  // EventResolver
  using EventResolver = Func<bool(const Event&)>;
}