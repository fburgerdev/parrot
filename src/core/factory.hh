#pragma once
#include "common.hh"

namespace Parrot {
  // Factory
  template<class T>
  class Factory {
  public:
    // (constructor)
    Factory() = default;
    // (destructor)
    virtual ~Factory() = default;

    // create
    virtual UniquePtr<T> create() const = 0;
  };

  // BasicFactory
  template<class T, class Base>
  class BasicFactory : public T, public Factory<Base> {
  public:
    // (constructor)
    using T::T;

    // create
    virtual UniquePtr<Base> create() const override;
  };

  // create
  template<class T, class Base>
  UniquePtr<Base> BasicFactory<T, Base>::create() const {
    return std::make_unique<T>(static_cast<const T&>(*this));
  }
}