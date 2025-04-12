#pragma once

namespace Parrot {
  template<class T>
  RNG<T>::RNG()
    : _generator(_device()) {
  }
  template<class T>
  RNG<T>::RNG(uint seed)
    : _generator(_device()) {
    _generator.seed(seed);
  }

  template<class T>
  T RNG<T>::random(T min, T max) {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(_generator);
  }
  template<class T>
  Vec2<T> RNG<T>::random2() {
    return normalized(
      Vec2<T>(random(-1, +1), random(-1, +1))
    );
  }
  template<class T>
  Vec3<T> RNG<T>::random3() {
    return normalized(
      Vec3<T>(random(-1, +1), random(-1, +1), random(-1, +1))
    );
  }
  template<class T>
  Vec4<T> RNG<T>::random4() {
    return normalized(
      Vec4<T>(random(-1, +1), random(-1, +1), random(-1, +1), random(-1, +1))
    );
  }
}