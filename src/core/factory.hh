#pragma once
#include "common.hh"

namespace Parrot {
  template<class T>
  class Factory {
  public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual UniquePtr<T> create() const = 0;
  };

  template<class T, class Base>
  class BasicFactory : public T, public Factory<Base> {
  public:
    using T::T;

    virtual UniquePtr<Base> create() const override;
  };
}
#include "factory_impl.hh"