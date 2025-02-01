#pragma once
#include "basic_math.hh"

namespace Parrot {
  // Mat
  template<typename T, usize N, usize M = N>
  struct Mat {
  public:
    // (constructor)
    Mat() = default;
    template<typename U>
    Mat(const Mat<U, N, M>& mat) {
      for (usize i = 0; i < N * M; ++i) {
        _array.at(i) = T(mat.at(i));
      }
    }
    // at
    T& at(usize index) {
      return _array.at(index);
    }
    const T& at(usize index) const {
      return _array.at(index);
    }
    T& at(usize n, usize m) {
      return _array.at(M * n + m);
    }
    const T& at(usize n, usize m) const {
      return _array.at(M * n + m);
    }
    // data
    T* data() {
      return _array.data();
    }
    const T* data() const {
      return _array.data();
    }
    // <=> (compare)
    auto operator<=>(const Mat<T, N, M>&) const = default;
  private:
    Array<T, N * M> _array;
  };
  // Marix2x1
  template<typename T>
  struct Mat<T, 2, 1> {
    // (constructor)
    Mat() = default;
    Mat(T val)
      : x(val), y(val) {}
    Mat(T x, T y)
      : x(x), y(y) {}
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec)
      : x(T(vec.at(0))), y(T(vec.at(1))) {}
    // at
    T& at(usize index) {
      return index == 0 ? x : y;
    }
    const T& at(usize index) const {
      return index == 0 ? x : y;
    }
    T& at(usize n, usize m) {
      return at(n);
    }
    const T& at(usize n, usize m) const {
      return at(n);
    }
    // <=> (compare)
    auto operator<=>(const Mat<T, 2, 1>&) const = default;

    // x, y
    T x, y;
  };
  // Mat3x1
  template<typename T>
  struct Mat<T, 3, 1> {
    // (constructor)
    Mat() = default;
    Mat(T val)
      : x(val), y(val), z(val) {}
    Mat(T x, T y, T z)
      : x(x), y(y), z(z) {}
    Mat(const Mat<T, 2, 1>& xy, T z)
      : x(xy.x), y(xy.y), z(z) {}
    Mat(T x, const Mat<T, 2, 1>& yz)
      : x(x), y(yz.x), z(yz.y) {}
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec)
      : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)) {}
    template<typename U>
    Mat(const Mat<U, 2, 1>& vec)
      : x(vec.at(0)), y(vec.at(1)), z(0) {}
    // at
    T& at(usize index) {
      return index == 0 ? x : index == 1 ? y : z;
    }
    const T& at(usize index) const {
      return index == 0 ? x : index == 1 ? y : z;
    }
    T& at(usize n, usize m) {
      return at(n);
    }
    const T& at(usize n, usize m) const {
      return at(n);
    }
    // <=> (compare)
    auto operator<=>(const Mat<T, 3, 1>&) const = default;
    
    // x, y, z
    T x, y, z;
  };
  // Mat4x1
  template<typename T>
  struct Mat<T, 4, 1> {
    // (constructor)
    Mat() = default;
    Mat(T val)
      : x(val), y(val), z(val), w(val) {}
    Mat(T x, T y, T z, T w)
      : x(x), y(y), z(z), w(w) {}
    Mat(const Mat<T, 2, 1>& xy, T z, T w)
      : x(xy.x), y(xy.y), z(z), w(w) {}
    Mat(T x, const Mat<T, 2, 1>& yz, T w)
      : x(x), y(yz.x), z(yz.y), w(w) {}
    Mat(T x, T y, const Mat<T, 2, 1>& zw)
      : x(x), y(y), z(zw.x), w(zw.y) {}
    Mat(const Mat<T, 3, 1>& xyz, T w)
      : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
    Mat(T x, const Mat<T, 3, 1>& yzw)
      : x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec)
      : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)), w(vec.at(3)) {}
    template<typename U>
    Mat(const Mat<U, 2, 1>& vec)
      : x(vec.at(0)), y(vec.at(1)), z(0), w(0) {}
    template<typename U, usize N>
    Mat(const Mat<U, 3, 1>& vec)
      : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)), w(0) {}
    // at
    T& at(usize index) {
      return index == 0 ? x : index == 1 ? y : index == 2 ? z : w;
    }
    const T& at(usize index) const {
      return index == 0 ? x : index == 1 ? y : index == 2 ? z : w;
    }
    T& at(usize n, usize m) {
      return at(n);
    }
    const T& at(usize n, usize m) const {
      return at(n);
    }
    // <=> (compare)
    auto operator<=>(const Mat<T, 4, 1>&) const = default;

    // x, y, z, w
    T x, y, z, w;
  };

  // zeros
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> zeros() {
    Mat<T, N, M> mat;
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) = 0;
    }
    return mat;
  }
  // identity
  template<typename T, usize N>
  Mat<T, N> identity() {
    Mat<T, N> mat = zeros<T, N>();
    for (usize n = 0; n < N; ++n) {
      mat.at(n, n) = 1;
    }
    return mat;
  }

  // - (unary)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat) {
    Mat<T, N, M> out;
    for (usize i = 0; i < N * M; ++i) {
      out.at(i) = -mat.at(i);
    }
    return out;
  }
  // +=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator+=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) += other.at(i);
    }
    return mat;
  }
  // -=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator-=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) -= other.at(i);
    }
    return mat;
  }
  // *=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator*=(Mat<T, N, M>& mat, T scalar) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) *= scalar;
    }
    return mat;
  }
  // /=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator/=(Mat<T, N, M>& mat, T scalar) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) /= scalar;
    }
    return mat;
  }
  // +
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator+(const Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    Mat<T, N, M> out(mat);
    out += other;
    return out;
  }
  // -
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    Mat<T, N, M> out(mat);
    out -= other;
    return out;
  }
  // * (scalar)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator*(const Mat<T, N, M>& mat, T scalar) {
    Mat<T, N, M> out(mat);
    out *= scalar;
    return out;
  }
  // / (scalar)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator/(const Mat<T, N, M>& mat, T scalar) {
    Mat<T, N, M> out(mat);
    out /= scalar;
    return out;
  }
  // *
  template<typename T, usize N, usize M, usize L>
  Mat<T, N, L> operator*(const Mat<T, N, M>& mat1, const Mat<T, M, L>& mat2) {
    Mat<T, N, L> out = zeros<T, N, L>();
    for (usize n = 0; n < N; ++n) {
      for (usize l = 0; l < L; ++l) {
        for (usize m = 0; m < M; ++m) {
          out.at(n, l) += mat1.at(n, m) * mat2.at(m, l);
        }
      }
    }
    return out;
  }
  template<typename T, usize N>
  Mat<T, N>& operator*=(Mat<T, N>& mat1, const Mat<T, N>& mat2) {
    mat1 = mat1 * mat2;
    return mat1;
  }

  // dot
  template<typename T, usize N, usize M = N>
  T dot(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
    T out = 0;
    for (usize i = 0; i < N * M; ++i) {
      out += mat1.at(i) * mat2.at(i);
    }
    return out;
  }
  // magnitude
  template<typename T, usize N, usize M = N>
  T magnitude(const Mat<T, N, M>& mat) {
    return std::sqrt(dot(mat, mat));
  }
  // length
  template<typename T, usize N, usize M = N>
  T length(const Mat<T, N, M>& mat) {
    return magnitude(mat);
  }
  template<typename T, usize N, usize M = N>
  T dist(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
    return length(mat2 - mat1);
  }

  // normalize(d)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& normalize(Mat<T, N, M>& mat) {
    return mat /= length(mat);
  }
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> normalized(const Mat<T, N, M>& mat) {
    return mat / length(mat);
  }

  // transpose(d)
  template<typename T, usize N>
  Mat<T, N>& transpose(Mat<T, N>& mat) {
    for (usize n1 = 0; n1 < N; ++n1) {
      for (usize n2 = 0; n2 < n1; ++n2) {
        mat.at(N * n2 + n1) = mat.at(N * n1 + n2);
      }
    }
    return mat;
  }
  template<typename T, usize N, usize M = N>
  Mat<T, M, N> transposed(const Mat<T, N, M>& mat) {
    Mat<T, M, N> out;
    for (usize n = 0; n < N; ++n) {
      for (usize m = 0; m < M; ++m) {
        out.at(N * m + n) = mat.at(M * n + m);
      }
    }
    return out;
  }

  // insert
  template<typename T, usize N1, usize M1, usize N2, usize M2>
  Mat<T, N1, M1>& insert(
    Mat<T, N1, M1>& dest, const Mat<T, N2, M2>& src,
    Mat<uint, 2, 1> origin = { 0, 0 }
  ) {
    for (usize n = 0; n < min(N1 - origin.x, N2); ++n) {
      for (usize m = 0; m < min(M1 - origin.y, M2); ++m) {
        dest.at(origin.x + n, origin.y + m) = src.at(n, m);
      }
    }
    return dest;
  }
  // resize
  template<typename T, usize N1, usize M1, usize N2, usize M2>
  Mat<T, N1, M1> resize(
    const Mat<T, N2, M2>& mat, const Mat<uint, 2, 1>& origin = { 0, 0 }
  ) {
    Mat<T, N1, M1> out = zeros<T, N1, M1>();
    insert(out, mat, origin);
    return out;
  }

  // <<
  template<typename T, usize N, usize M = N>
  ostream& operator<<(ostream& stream, const Mat<T, N, M>& mat) {
    if constexpr (M == 1) {
      stream << "{ ";
      for (usize n = 0; n < N; ++n) {
        stream << mat.at(n);
        if (n + 1 < N) {
          stream << ", ";
        }
      }
      stream << " }";
    }
    else {
      stream << "{ ";
      for (usize n = 0; n < N; ++n) {
        stream << "{ ";
        for (usize m = 0; m < M; ++m) {
          stream << mat.at(n, m);
          if (m + 1 < M) {
            stream << ", ";
          }
        }
        stream << " }";
        if (n + 1 < N) {
          stream << ", ";
        }
      }
      stream << " }";
    }
    return stream;
  }

  // MatNxM
  template<typename T = DefaultFloat>
  using Mat2x2 = Mat<T, 2, 2>;
  template<typename T = DefaultFloat>
  using Mat2x3 = Mat<T, 2, 3>;
  template<typename T = DefaultFloat>
  using Mat2x4 = Mat<T, 2, 4>;
  template<typename T = DefaultFloat>
  using Mat3x2 = Mat<T, 3, 2>;
  template<typename T = DefaultFloat>
  using Mat3x3 = Mat<T, 3, 3>;
  template<typename T = DefaultFloat>
  using Mat3x4 = Mat<T, 3, 4>;
  template<typename T = DefaultFloat>
  using Mat4x2 = Mat<T, 4, 2>;
  template<typename T = DefaultFloat>
  using Mat4x3 = Mat<T, 4, 3>;
  template<typename T = DefaultFloat>
  using Mat4x4 = Mat<T, 4, 4>;
  // VecN
  template<typename T, usize N>
  using Vec = Mat<T, N, 1>;
  template<typename T = DefaultFloat>
  using Vec2 = Vec<T, 2>;
  template<typename T = DefaultFloat>
  using Vec3 = Vec<T, 3>;
  template<typename T = DefaultFloat>
  using Vec4 = Vec<T, 4>;
}