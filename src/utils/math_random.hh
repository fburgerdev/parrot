#pragma once
#include "math_matrix.hh"
#include <random>

namespace Parrot {
  template<class T = DefaultFloat>
  class RNG {
  public:
    RNG();
    RNG(uint seed);

    T random(T min = 0.0, T max = 1.0);
    Vec2<T> random2();
    Vec3<T> random3();
    Vec4<T> random4();
  private:
    std::random_device _device;
    std::mt19937 _generator;
  };
}
#include "math_random_impl.hh"