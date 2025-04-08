#pragma once

namespace Parrot {
  // create
  template<class T, class Base>
  UniquePtr<Base> BasicFactory<T, Base>::create() const {
    return std::make_unique<T>(static_cast<const T&>(*this));
  }
}