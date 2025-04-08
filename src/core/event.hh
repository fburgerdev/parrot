#pragma once
#include "common.hh"

namespace Parrot {
  class Scriptable;
  class Event {
  public:
    Event() = default;
    Event(Scriptable* target);

    virtual strview getDebugType() const;

    Scriptable* target = nullptr;
  };
  using EventResolver = Func<bool(const Event&)>;
}