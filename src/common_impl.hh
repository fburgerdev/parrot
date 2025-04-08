#pragma once

namespace Parrot {
  // holds
  template<class T, class... Args>
  bool holds(const Variant<Args...>& variant) {
    return std::holds_alternative<T>(variant);
  }
}