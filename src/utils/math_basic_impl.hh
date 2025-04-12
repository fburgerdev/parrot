#pragma once

namespace Parrot {
  template<class T>
  constexpr T clamp(T value, T min, T max) {
    return (value < min ? min : (value > max ? max : value));
  }

  template<class First, class... Rest>
  constexpr First min(First left, Rest&&... rest) {
    if constexpr (sizeof...(Rest)) {
      First right = First(min(std::forward<Rest>(rest)...));
      return right < left ? right : left;
    }
    else {
      return left;
    }
  }
  template<class First, class... Rest>
  constexpr First max(First left, Rest&&... rest) {
    if constexpr (sizeof...(Rest)) {
      First right = First(max(std::forward<Rest>(rest)...));
      return left < right ? right : left;
    }
    else {
      return left;
    }
  }

  template<class T>
  constexpr T pow(T base, usize exponent) {
    T out = (T)1.0;
    for (usize i = 0; i < exponent; ++i) {
      out *= base;
    }
    return out;
  }
}