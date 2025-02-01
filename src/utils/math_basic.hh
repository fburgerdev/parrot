#pragma once
#include "common.hh"

namespace Parrot {
  // default
  using DefaultFloat = float32;

  // constants
  // :: PI
  template<class T = DefaultFloat>
  constexpr T PI;
  template<>
  constexpr float32 PI<float32> = 3.1415926F;
  template<>
  constexpr float64 PI<float64> = 3.1415926;

  // clamp
  template<class T = DefaultFloat>
  T clamp(T value, T min, T max) {
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
}