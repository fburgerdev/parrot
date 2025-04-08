#pragma once
#include "math_random.hh"

namespace Parrot {
  // quinticfade
  template<class T = DefaultFloat>
  T quinticfade(T x);

  // generatePerlin2D
  // :: single layer
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, RNG<T>& rng
  );
  // :: (no random-generator)
  template<class T>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size
  );
  // :: multiple layers
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, usize octaves, RNG<T>& rng
  );
  // :: (no random-generator)
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, usize octaves
  );
}
#include "math_perlin_impl.hh"