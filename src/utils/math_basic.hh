#pragma once
#include "common.hh"

namespace Parrot {
  /// @brief Floating-point type used by default.
  using DefaultFloat = float32;

  /// @brief Mathematical constant pi.
  /// @tparam T Floating-point type
  template<class T = DefaultFloat>
  constexpr T PI = 3.1415926;
  /// @brief Mathematical constant square-root of 2.
  /// @tparam T Floating-point type
  template<class T = DefaultFloat>
  constexpr T SQRT_2 = 1.4142135;

  /// @tparam T Floating-point type
  /// @param value Input value to clamp
  /// @param min Minimum value for @c value
  /// @param max Maximum value for @c value
  /// @retval @c value if @c min <= @c value <= @c min
  /// @retval @c min if @c value < @c min
  /// @retval @c max if @c max < @c value
  template<class T = DefaultFloat>
  constexpr T clamp(T value, T min, T max);

  /// @param left Left most value
  /// @param rest Remaining values
  /// @return Minimum of all given values
  template<class First, class... Rest>
  constexpr First min(First left, Rest&&... rest);
  /// @param left Left most value
  /// @param rest Remaining values
  /// @return Maximum of all given values
  template<class First, class... Rest>
  constexpr First max(First left, Rest&&... rest);

  /// @tparam T Floating-point type
  /// @return @c base to the power of @c exponent
  template<class T = DefaultFloat>
  constexpr T pow(T base, usize exponent);  
}
#include "math_basic_impl.hh"