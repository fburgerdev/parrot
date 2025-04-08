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

  // (constructor)
  template<class T>
  RNG<T>::RNG()
    : _generator(_device()) {}
  template<class T>
  RNG<T>::RNG(uint seed)
    : _generator(_device()) {
    _generator.seed(seed);
  }

  // random
  // :: 1D
  template<class T>
  T RNG<T>::random(T min, T max) {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(_generator);
  }
  // :: 2D
  template<class T>
  Vec2<T> RNG<T>::random2() {
    return normalized(
      Vec2<T>(random(-1, +1), random(-1, +1))
    );
  }
  // :: 3D
  template<class T>
  Vec3<T> RNG<T>::random3() {
    return normalized(
      Vec3<T>(random(-1, +1), random(-1, +1), random(-1, +1))
    );
  }
  // :: 4D
  template<class T>
  Vec4<T> RNG<T>::random4() {
    return normalized(
      Vec4<T>(random(-1, +1), random(-1, +1), random(-1, +1), random(-1, +1))
    );
  }
}