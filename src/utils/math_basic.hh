#pragma once
#include "common.hh"

namespace Parrot {
  // default
  using DefaultFloat = float32;

  // constants
  // :: pi
  template<class T = DefaultFloat>
  constexpr T PI;
  template<>
  constexpr float32 PI<float32> = 3.1415926F;
  template<>
  constexpr float64 PI<float64> = 3.1415926;
  // :: sqrt(2)
  template<class T = DefaultFloat>
  constexpr T SQRT_2;
  template<>
  constexpr float32 SQRT_2<float32> = 1.4142135F;
  template<>
  constexpr float64 SQRT_2<float64> = 1.4142135;

  // clamp
  template<class T = DefaultFloat>
  constexpr T clamp(T value, T min, T max);

  // min
  template<class First, class... Rest>
  constexpr First min(First left, Rest&&... rest);
  // max
  template<class First, class... Rest>
  constexpr First max(First left, Rest&&... rest);

  // pow
  template<class T = DefaultFloat>
  constexpr T pow(T base, usize exponent);

  // ---
  
  // clamp
  template<class T>
  constexpr T clamp(T value, T min, T max) {
    return (value < min ? min : (value > max ? max : value));
  }

  // min
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
  // max
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

  // pow
  template<class T>
  constexpr T pow(T base, usize exponent) {
    T out = (T)1.0;
    for (usize i = 0; i < exponent; ++i) {
      out *= base;
    }
    return out;
  }
}