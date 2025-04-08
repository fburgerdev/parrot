#pragma once
#include "math_matrix.hh"
#include <random>

namespace Parrot {
  // RNG
  template<class T = DefaultFloat>
  class RNG {
  public:
    // (constructor)
    RNG();
    RNG(uint seed);

    // random
    // :: 1D
    T random(T min = 0.0, T max = 1.0);
    // :: 2D
    Vec2<T> random2();
    // :: 3D
    Vec3<T> random3();
    // :: 4D
    Vec4<T> random4();
  private:
    std::random_device _device;
    std::mt19937 _generator;
  };
}
#include "math_random_impl.hh"