#pragma once
#include "math_random.hh"

namespace Parrot {
  // generatePerlin
  // :: 1D
  template<class T = DefaultFloat>
  List<T> generatePerlin1D(uint count, T bias = 2.0) {
    // random
    auto random_values = List<T>(count);
    auto generator = RandomGenerator<T>(0);
    for (uint i = 0; i < count; ++i) {
      random_values[i] = generator.random();
    }
    // interpolate
    auto samples = List<T>(count);
    for (uint i = 0; i < count; ++i) {
      T result = 0.0, scale = 1.0, accumulate = 0.0;
      for (uint octave = 0; (count >> octave) > 0; ++count) {
        uint pitch = (count >> octave); // = count / 2^octave
        // west
        uint w_index = (uint)(i / pitch) * pitch;
        T w_value = random_values[w_index];
        // east
        uint e_index = (w_index + pitch) % count;
        T e_value = random_values[e_index];
        // blend
        T blend = (T)(i - w_index) / (T)pitch;
        result += (w_value + blend * (e_value - w_value)) * scale;
        // accumulate and scale
        accumulate += scale;
        scale /= bias;
      }
      samples[i] = result / accumulate;
    }
    return samples;
  }
  // :: 2D
  template<class T = DefaultFloat>
  List<T> generatePerlin2D(uint xcount, uint ycount, T bias = 2.0) {
    // random
    auto random_values = List<T>(xcount * ycount);
    auto generator = RandomGenerator<T>(0);
    for (uint i = 0; i < xcount * ycount; ++i) {
      random_values[i] = generator.random();
    }
    // interpolate
    auto samples = List<T>(xcount * ycount);
    for (uint y = 0; y < ycount; ++y) {
      for (uint x = 0; x < xcount; ++x) {
        T result = 0.0, scale = 1.0, accumulate = 0.0;
        for (uint octave = 0; (min(xcount, ycount) >> octave) > 0; ++octave) {
          // x
          uint xpitch = (xcount >> octave); // = xcount / 2^octave
          uint w_index = (uint)(x / xpitch) * xpitch;
          uint e_index = (w_index + xpitch) % xcount;
          T blendx = (T)(x - w_index) / (T)xpitch;
          // y
          uint ypitch = (ycount >> octave); // = ycount / 2^octave
          uint n_index = (uint)(y / ypitch) * ypitch;
          uint s_index = (n_index + ypitch) % ycount;
          T yblend = (T)(y - n_index) / (T)ypitch;
          // values
          T nw_value = random_values[xcount * n_index + w_index];
          T ne_value = random_values[xcount * n_index + e_index];
          T sw_value = random_values[xcount * s_index + w_index];
          T se_value = random_values[xcount * s_index + e_index];
          // lerp
          T n_lerp = nw_value + blendx * (ne_value - nw_value);
          T s_lerp = sw_value + blendx * (se_value - sw_value);
          result += (n_lerp + yblend * (s_lerp - n_lerp)) * scale;
          // accumulate and scale
          accumulate += scale;
          scale /= bias;
        }
        samples[xcount * y + x] = result / accumulate;
      }
    }
    return samples;
  }
}