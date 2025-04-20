#pragma once
#include "common.hh"

namespace Parrot {
  /// @ingroup Internals
  /// @brief Interface for class that creates instances of @c T.
  /// @tparam T The type of the instances to be created
  /// @tparam Args The arguments passed to @c create to create an instance
  template<class T, class... Args>
  class Factory {
  public:
    Factory() = default;
    virtual ~Factory() = default;

    virtual UniquePtr<T> create(Args&&... args) const = 0;
  };

  /// @ingroup Internals
  /// @brief A basic implementation for Factory<Base> that
  /// calls a given method (usually a lambda) to create instances.
  /// @tparam T The type of the instances to be created
  /// @tparam Args The arguments passed to @c create to create an instance
  template<class T, class... Args>
  class LambdaFactory : public Factory<T> {
  public:
    LambdaFactory(Func<UniquePtr<T>(Args&&...)> func);

    virtual UniquePtr<T> create(Args&&... args) const override;
  private:
    Func<UniquePtr<T>(Args&&...)> _func;
  };

  /// @ingroup Internals
  /// @brief A basic implementation for Factory<Base> that
  /// copies an existing instance to create instances.
  /// @tparam T The type of the instances to be created
  /// @tparam Base The base type to be returnend from the @c create method
  template<class T, class Base>
  class CopyFactory : public T, public Factory<Base> {
  public:
    using T::T;

    virtual UniquePtr<Base> create() const override;
  };
}
#include "factory_impl.hh"