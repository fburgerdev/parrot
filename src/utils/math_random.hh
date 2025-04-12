#pragma once
#include "math_matrix.hh"
#include <random>

namespace Parrot {
  /// @brief Random-Number-Generator to generate floating point numbers.
  /// @tparam T Floating point type to generate
  template<class T = DefaultFloat>
  class RNG {
  public:
    /// @brief Construct Random-Number-Generator with random seed.
    RNG();
    /// @brief Construct Random-Number-Generator with given seed.
    RNG(uint seed);

    /// @brief Generate random number within certain bounds.
    T random(T min = 0.0, T max = 1.0);
    /// @brief Generate normalized 2-dimensional vector,
    /// that points in a random direction.
    Vec2<T> random2();
    /// @brief Generate normalized 3-dimensional vector,
    /// that points in a random direction.
    Vec3<T> random3();
    /// @brief Generate normalized 4-dimensional vector,
    /// that points in a random direction.
    Vec4<T> random4();
  private:
    std::random_device _device;
    std::mt19937 _generator;
  };
}
#include "math_random_impl.hh"