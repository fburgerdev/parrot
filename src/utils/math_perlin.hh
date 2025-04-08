#pragma once
#include "math_random.hh"

namespace Parrot {
  template<class T = DefaultFloat>
  T quinticfade(T x);

  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, RNG<T>& rng
  );
  template<class T>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size
  );
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, usize octaves, RNG<T>& rng
  );
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, usize octaves
  );
}
#include "math_perlin_impl.hh"