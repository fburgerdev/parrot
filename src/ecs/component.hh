#pragma once
#include "common.hh"

namespace Parrot {
  // Component
  class Component {
  public:
    // (constructor)
    Component() = default;
    // (destructor)
    virtual ~Component() = default;

    // update
    virtual void update(float32 update);
    // getID
    virtual usize getID() const = 0;
  };
}