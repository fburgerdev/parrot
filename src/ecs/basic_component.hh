#pragma once
#include "component.hh"

namespace Parrot {
  // BasicComponent
  template<class T>
  class BasicComponent : public T, public Component {
  public:
    // (constructor)
    using T::T;
    // (destructor)
    virtual ~BasicComponent() = default;

    // getID
    virtual usize getID() const override;
  };
}
#include "basic_component_impl.hh"