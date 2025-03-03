#pragma once
#include "math_random.hh"

namespace Parrot {
  // quinticfade
  template<class T = DefaultFloat>
  T quinticfade(T x) {
    return 6 * pow(x, 5) - 15 * pow(x, 4) + 10 * pow(x, 3);
  }
  
  // generatePerlin2D
  // :: single layer
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, RNG<T>& rng
  ) {
    // grid
    List<Vec2<T>> grid(grid_size.x * grid_size.y);
    for (Vec2<T>& gradient : grid) {
      gradient = rng.random2();
    }

    // samples
    List<T> samples(sample_size.x * sample_size.y);
    for (uint iy = 0; iy < sample_size.y; ++iy) {
      for (uint ix = 0; ix < sample_size.x; ++ix) {
        // grid cell
        T x = ((grid_size.x - 1) / (T)sample_size.x) * (ix + (T)0.5);
        T y = ((grid_size.y - 1) / (T)sample_size.y) * (iy + (T)0.5);
        uint x0 = uint(x);
        uint y0 = uint(y);
        T s = x - x0;
        T t = y - y0;
        
        // gradients
        Vec2<T> g00 = grid.at(grid_size.x * (y0 + 0) + (x0 + 0));
        Vec2<T> g01 = grid.at(grid_size.x * (y0 + 0) + (x0 + 1));
        Vec2<T> g10 = grid.at(grid_size.x * (y0 + 1) + (x0 + 0));
        Vec2<T> g11 = grid.at(grid_size.x * (y0 + 1) + (x0 + 1));

        // dot products
        T d0 = s * g00.x + t * g00.y;
        T d1 = (s - 1) * g01.x + t * g01.y;
        T d2 = s * g10.x + (t - 1) * g10.y; 
        T d3 = (s - 1) * g11.x + (t - 1) * g11.y;
        
        // smoothing
        T u = quinticfade(s);
        T v = quinticfade(t);

        // interpolation
        T i0 = (1 - u) * d0 + u * d1;
        T i1 = (1 - u) * d2 + u * d3;
        T sample = (1 - v) * i0 + v * i1;

        samples.at(sample_size.x * iy + ix) = sample;
      }
    }
    return samples;
  }
  // :: (no random-generator)
  template<class T>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size
  ) {
    auto rng = RNG<T>();
    return generatePerlin2D(sample_size, grid_size, rng);
  }
  // :: multiple layers
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, usize octaves, RNG<T>& rng
  ) {
    List<T> samples(sample_size.x * sample_size.y);
    for (T& sample : samples) {
      sample = 0;
    }
    T factor = (T)1, sum = (T)0;
    for (usize n = 0; n < octaves; ++n) {
      List<T> octave_samples = generatePerlin2D(sample_size, grid_size, rng);
      for (usize i = 0; i < samples.size(); ++i) {
        samples.at(i) += octave_samples.at(i) * factor;
      }
      grid_size *= uint(2);
      sum += factor;
      factor /= 2;
    }
    for (T& sample : samples) {
      sample /= sum;
    }
    return samples;
  }
  // :: (no random-generator)
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(
    Vec2u sample_size, Vec2u grid_size, usize octaves
  ) {
    auto rng = RNG<T>();
    return generareatePerlin2D(sample_size, grid_size, octaves, rng);
  }
}