#pragma once
#include "math_matrix.hh"

namespace Parrot {
  // calcTranslationMatrix
  template<typename T = DefaultFloat>
  Mat4x4<T> calcTranslationMatrix(const Vec3<T>& translation) {
    Mat4x4<T> out = identity<T, 4>();
    out.at(0, 3) = translation.x;
    out.at(1, 3) = translation.y;
    out.at(2, 3) = translation.z;
    return out;
  }
  // calcScaleMatrix
  template<typename T = DefaultFloat>
  Mat4x4<T> calcScaleMatrix(const Vec3<T>& scale) {
    Mat4x4<T> out = identity<T, 4>();
    out.at(0, 0) *= scale.x;
    out.at(1, 1) *= scale.y;
    out.at(2, 2) *= scale.z;
    return out;
  }
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
  Mat4x4<T> calcRotationMatrix(const Vec3<T>& euler_rotation) {
    Mat4x4<T> out = zeros<T, 4>();
    T sina = std::sin(euler_rotation.y);
    T cosa = std::cos(euler_rotation.y);
    T sinb = std::sin(euler_rotation.x);
    T cosb = std::cos(euler_rotation.x);
    T sinc = std::sin(euler_rotation.z);
    T cosc = std::cos(euler_rotation.z);

    // row 1
    out.at(0, 0) = cosa * cosc - sina * sinc * sinb;
    out.at(0, 1) = cosa * sinc + sina * sinb * cosc;
    out.at(0, 2) = -sina * cosb;
    // row 2
    out.at(1, 0) = -sinc * cosb;
    out.at(1, 1) = cosb * cosc;
    out.at(1, 2) = sinb;
    // row 3
    out.at(2, 0) = sina * cosc + cosa * sinc * sinb;
    out.at(2, 1) = sina * sinc - cosa * sinb * cosc;
    out.at(2, 2) = cosa * cosb;
    // row 4
    out.at(3, 3) = 1;
    return out;
  }

  // Transform
  template<class T = DefaultFloat>
  class Transform {
  public:
    // calcLocalModelMatrix
    Mat4x4<T> calcLocalModelMatrix() const {
      Mat4x4<T> translation_matrix = calcTranslationMatrix(position);
      Mat4x4<T> rotation_matrix = calcRotationMatrix(rotation);
      Mat4x4<T> scale_matrix = calcScaleMatrix(scale);
      return translation_matrix * rotation_matrix * scale_matrix;
    }
    // calcLocalViewMatrix
    Mat4x4<T> calcLocalViewMatrix() const {
      Mat4x4<T> translation_matrix = calcTranslationMatrix(-position);
      Mat4x4<T> rotation_matrix = transposed(calcRotationMatrix(rotation));
      return rotation_matrix * translation_matrix;
    }

    // position, rotation, scale
    Vec3<T> position = { 0.0F, 0.0F, 0.0F };
    Vec3<T> rotation = { 0.0F, 0.0F, 0.0F };
    Vec3<T> scale = { 1.0F, 1.0F, 1.0F };
  };
}