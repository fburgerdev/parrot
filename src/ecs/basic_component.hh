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

  // getID
  template<class T>
  usize BasicComponent<T>::getID() const {
    return typeid(BasicComponent<T>).hash_code();
  }
}