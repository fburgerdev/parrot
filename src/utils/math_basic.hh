#pragma once
#include "common.hh"

namespace Parrot {
  // default
  using DefaultFloat = float32; /* ASSET_API */

  // constants
  // :: PI
  template<class T = DefaultFloat>
  constexpr T PI;
  template<>
  constexpr float32 PI<float32> = 3.1415926F;
  template<>
  constexpr float64 PI<float64> = 3.1415926;
  // :: SQRT_2
  template<class T = DefaultFloat>
  constexpr T SQRT_2;
  template<>
  constexpr float32 SQRT_2<float32> = 1.4142135F;
  template<>
  constexpr float64 SQRT_2<float64> = 1.4142135;

  // clamp
  template<class T = DefaultFloat>
  constexpr T clamp(T value, T min, T max) {
    return (value < min ? min : (value > max ? max : value));
  }

  // min
  template<class TFirst, class... TRest>
  constexpr TFirst min(TFirst left, TRest&&... rest) {
    if constexpr (sizeof...(TRest)) {
      TFirst right = TFirst(min(std::forward<TRest>(rest)...));
      return right < left ? right : left;
    }
    else {
      return left;
    }
  }
  // max
  template<class TFirst, class... TRest>
  constexpr TFirst max(TFirst left, TRest&&... rest) {
    if constexpr (sizeof...(TRest)) {
      TFirst right = TFirst(max(std::forward<TRest>(rest)...));
      return left < right ? right : left;
    }
    else {
      return left;
    }
  }

  // pow
  template<class T = DefaultFloat>
  constexpr T pow(T base, usize exponent) {
    T out = (T)1.0;
    for (usize i = 0; i < exponent; ++i) {
      out *= base;
    }
    return out;
  }
}