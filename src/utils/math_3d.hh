#pragma once
#include "math_matrix.hh"

namespace Parrot {
  // calcTranslationMatrix
  template<typename T = DefaultFloat>
  Mat4x4<T> calcTranslationMatrix(const Vec3<T>& translation);
  // calcScaleMatrix
  template<typename T = DefaultFloat>
  Mat4x4<T> calcScaleMatrix(const Vec3<T>& scale);
  /*
    Note that the following function calcs a matrix that performs rotations in
    the following order:
    y -> x -> z
    which is the "yaw, pitch, roll" pattern when having the following
    coordinate system
    y
    |  z
    | /
    |/
    ------x
    and when looking in the +z direction
  */
  // calcRotationMatrix (using euler radius)
  template<typename T = DefaultFloat>
  Mat4x4<T> calcRotationMatrix(const Vec3<T>& euler_rotation);

  // Transform
  template<class T = DefaultFloat>
  class Transform {
  public:
    // calcLocalModelMatrix
    Mat4x4<T> calcLocalModelMatrix() const;
    // calcLocalViewMatrix
    Mat4x4<T> calcLocalViewMatrix() const;

    // position, rotation, scale
    Vec3<T> position = { 0.0F, 0.0F, 0.0F };
    Vec3<T> rotation = { 0.0F, 0.0F, 0.0F };
    Vec3<T> scale = { 1.0F, 1.0F, 1.0F };
  };
}
#include "math_3d_impl.hh"