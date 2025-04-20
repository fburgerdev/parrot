#pragma once

namespace Parrot {
  template<class T, class... Args>
  LambdaFactory<T, Args...>::LambdaFactory(Func<UniquePtr<T>(Args&&...)> func)
    : _func(std::move(func)) {}
  template<class T, class... Args>
  UniquePtr<T> LambdaFactory<T, Args...>::create(Args&&... args) const {
    return _func(args...);
  }

  template<class T, class Base>
  UniquePtr<Base> CopyFactory<T, Base>::create() const {
    return std::make_unique<T>(static_cast<const T&>(*this));
  }
}