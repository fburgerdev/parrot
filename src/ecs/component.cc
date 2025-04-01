#include "common.hh"
#include "component.hh"
#include "core/log.hh"

namespace Parrot {
  // update
  void Component::update(float32) {
    LOG_ECS_TRACE("component update (addr = {})", this);
  }
}