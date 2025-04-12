#pragma once

namespace Parrot {
  template<class T, class... Args>
  bool holds(const Variant<Args...>& variant) {
    return std::holds_alternative<T>(variant);
  }
}