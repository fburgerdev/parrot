#include "common.hh"
#include "event.hh"

namespace Parrot {
  // (constructor)
  Event::Event(Scriptable* target)
    : target(target) {
  }
  // getDebugType
  strview Event::getDebugType() const {
    return "Event";
  }
}