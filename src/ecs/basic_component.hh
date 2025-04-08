#pragma once
#include "component.hh"

namespace Parrot {
  template<class T>
  class BasicComponent : public T, public Component {
  public:
    using T::T;
    virtual ~BasicComponent() = default;

    virtual usize getID() const override;
  };
}
#include "basic_component_impl.hh"