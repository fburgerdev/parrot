#pragma once
#include "common.hh"

namespace Parrot {
  class Component {
  public:
    Component() = default;
    virtual ~Component() = default;

    virtual void update(float32 update);
    virtual usize getID() const = 0;
  };
}