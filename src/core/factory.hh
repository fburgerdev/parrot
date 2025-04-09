#pragma once
#include "common.hh"

namespace Parrot {
  /// @ingroup Internals
  /// @brief Interface for class that creates instances of @c T.
  /// @tparam T The type of the instances to be created
  template<class T>
  class Factory {
  public:
    Factory() = default;
    virtual ~Factory() = default;

    /// @return Created instance
    virtual UniquePtr<T> create() const = 0;
  };

  /// @ingroup Internals
  /// @brief A basic implementation for Factory<Base> that creates
  /// copies of an existing instance.
  /// @tparam T The type of the instances to be created
  /// @tparam Base The base type to be returnend from the @c create method
  template<class T, class Base>
  class BasicFactory : public T, public Factory<Base> {
  public:
    using T::T;

    /// @return Created UniquePtr<T> cast to UniquePtr<Base>
    virtual UniquePtr<Base> create() const override;
  };
}
#include "factory_impl.hh"