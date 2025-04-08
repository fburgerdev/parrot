#pragma once
#include "math_basic.hh"

namespace Parrot {
  // Mat
  template<typename T, usize N, usize M = N>
  struct Mat {
  public:
    // Type
    using Type = T;
    // (static) ROWS, COLS
    static constexpr usize ROWS = N, COLS = M;

    // (constructor)
    Mat() = default;
    template<typename U>
    Mat(const Mat<U, N, M>& mat);
    
    // at
    T& at(usize index);
    const T& at(usize index) const;
    T& at(usize n, usize m);
    const T& at(usize n, usize m) const;
    // data
    T* data();
    const T* data() const;

    // <=> (compare)
    auto operator<=>(const Mat<T, N, M>&) const = default;
  private:
    Array<T, N * M> _array;
  };
  // Mat2x1
  template<typename T>
  struct Mat<T, 2, 1> {
    // Type
    using Type = T;
    // (static) ROWS, COLS
    static constexpr usize ROWS = 2, COLS = 1;

    // (constructor)
    Mat() = default;
    Mat(T val);
    Mat(T x, T y);
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec);

    // at
    T& at(usize index);
    const T& at(usize index) const;
    T& at(usize n, usize m);
    const T& at(usize n, usize m) const;
    
    // <=> (compare)
    auto operator<=>(const Mat<T, 2, 1>&) const = default;

    // x, y
    T x, y;
  };
  // Mat3x1 
  template<typename T>
  struct Mat<T, 3, 1> {
    // Type
    using Type = T;
    // (static) ROWS, COLS
    static constexpr usize ROWS = 3, COLS = 1;

    // (constructor)
    Mat() = default;
    Mat(T val);
    Mat(T x, T y, T z);
    Mat(const Mat<T, 2, 1>& xy, T z);
    Mat(T x, const Mat<T, 2, 1>& yz);
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec);
    template<typename U>
    Mat(const Mat<U, 2, 1>& vec);
    
    // at
    T& at(usize index);
    const T& at(usize index) const;
    T& at(usize n, usize m);
    const T& at(usize n, usize m) const;
    
    // <=> (compare)
    auto operator<=>(const Mat<T, 3, 1>&) const = default;
    
    // x, y, z
    T x, y, z;
  };
  // Mat4x1
  template<typename T>
  struct Mat<T, 4, 1> {
    // Type
    using Type = T;
    // (static) ROWS, COLS
    static constexpr usize ROWS = 4, COLS = 1;

    // (constructor)
    Mat() = default;
    Mat(T val);
    Mat(T x, T y, T z, T w);
    Mat(const Mat<T, 2, 1>& xy, T z, T w);
    Mat(T x, const Mat<T, 2, 1>& yz, T w);
    Mat(T x, T y, const Mat<T, 2, 1>& zw);
    Mat(const Mat<T, 3, 1>& xyz, T w);
    Mat(T x, const Mat<T, 3, 1>& yzw);
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec);
    template<typename U>
    Mat(const Mat<U, 2, 1>& vec);
    template<typename U, usize N>
    Mat(const Mat<U, 3, 1>& vec);

    // at
    T& at(usize index);
    const T& at(usize index) const;
    T& at(usize n, usize m);
    const T& at(usize n, usize m) const;
    
    // <=> (compare)
    auto operator<=>(const Mat<T, 4, 1>&) const = default;

    // x, y, z, w
    T x, y, z, w;
  };

  // zeros
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> zeros();
  // identity
  template<typename T, usize N>
  Mat<T, N> identity();

  // - (unary)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat);
  // +=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator+=(Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  // -=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator-=(Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  // *=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator*=(Mat<T, N, M>& mat, T scalar);
  // /=
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator/=(Mat<T, N, M>& mat, T scalar);

  // +
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator+(const Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  // -
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  // * (scalar)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator*(const Mat<T, N, M>& mat, T scalar);
  // / (scalar)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator/(const Mat<T, N, M>& mat, T scalar);
  // *
  template<typename T, usize N, usize M, usize L>
  Mat<T, N, L> operator*(const Mat<T, N, M>& mat1, const Mat<T, M, L>& mat2);
  template<typename T, usize N>
  Mat<T, N>& operator*=(Mat<T, N>& mat1, const Mat<T, N>& mat2);

  // dot
  template<typename T, usize N, usize M = N>
  T dot(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2);
  // cross
  template<typename T>
  Mat<T, 3, 1> cross(const Mat<T, 3, 1>& v1, const Mat<T, 3, 1>& v2);
  // magnitude
  template<typename T, usize N, usize M = N>
  T magnitude(const Mat<T, N, M>& mat);
  // length
  template<typename T, usize N, usize M = N>
  T length(const Mat<T, N, M>& mat);
  // dist
  template<typename T, usize N, usize M = N>
  T dist(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2);

  // normalize(d)
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& normalize(Mat<T, N, M>& mat);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> normalized(const Mat<T, N, M>& mat);

  // transpose(d)
  template<typename T, usize N>
  Mat<T, N>& transpose(Mat<T, N>& mat);
  template<typename T, usize N, usize M = N>
  Mat<T, M, N> transposed(const Mat<T, N, M>& mat);

  // insert
  template<typename T, usize N1, usize M1, usize N2, usize M2>
  Mat<T, N1, M1>& insert(
    Mat<T, N1, M1>& dest, const Mat<T, N2, M2>& src,
    Mat<uint, 2, 1> origin = { 0, 0 }
  );
  // resize
  template<usize N1, usize M1, typename T, usize N2, usize M2>
  Mat<T, N1, M1> resize(
    const Mat<T, N2, M2>& mat, const Mat<uint, 2, 1>& origin = { 0, 0 }
  );
  // << (stream)
  template<typename T, usize N, usize M = N>
  ostream& operator<<(ostream& stream, const Mat<T, N, M>& mat);

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
  // :: int
  using Vec2i = Vec2<int>;
  using Vec3i = Vec3<int>;
  using Vec4i = Vec4<int>;
  // :: uint
  using Vec2u = Vec2<uint>;
  using Vec3u = Vec3<uint>;
  using Vec4u = Vec4<uint>;
  // :: float
  using Vec2f = Vec2<float>;
  using Vec3f = Vec3<float>;
  using Vec4f = Vec4<float>;
  // :: double
  using Vec2d = Vec2<double>;
  using Vec3d = Vec3<double>;
  using Vec4d = Vec4<double>;

  // ---

  //* Mat
  // (constructor)
  template<typename T, usize N, usize M>
  template<typename U>
  Mat<T, N, M>::Mat(const Mat<U, N, M>& mat) {
    for (usize i = 0; i < N * M; ++i) {
      _array.at(i) = T(mat.at(i));
    }
  }
  // at
  template<typename T, usize N, usize M>
  T& Mat<T, N, M>::at(usize index) {
    return _array.at(index);
  }
  template<typename T, usize N, usize M>
  const T& Mat<T, N, M>::at(usize index) const {
    return _array.at(index);
  }
  template<typename T, usize N, usize M>
  T& Mat<T, N, M>::at(usize n, usize m) {
    return _array.at(M * n + m);
  }
  template<typename T, usize N, usize M>
  const T& Mat<T, N, M>::at(usize n, usize m) const {
    return _array.at(M * n + m);
  }
  // data
  template<typename T, usize N, usize M>
  T* Mat<T, N, M>::data() {
    return _array.data();
  }
  template<typename T, usize N, usize M>
  const T* Mat<T, N, M>::data() const {
    return _array.data();
  }

  //* Mat2x1
  // (constructor)
  template<typename T>
  Mat<T, 2, 1>::Mat(T val)
    : x(val), y(val) {}
  template<typename T>
  Mat<T, 2, 1>::Mat(T x, T y)
    : x(x), y(y) {}
  template<typename T>
  template<typename U, usize N>
  Mat<T, 2, 1>::Mat(const Mat<U, N, 1>& vec)
    : x(T(vec.at(0))), y(T(vec.at(1))) {}
  // at
  template<typename T>
  T& Mat<T, 2, 1>::at(usize index) {
    return index == 0 ? x : y;
  }
  template<typename T>
  const T& Mat<T, 2, 1>::at(usize index) const {
    return index == 0 ? x : y;
  }
  template<typename T>
  T& Mat<T, 2, 1>::at(usize n, usize m) {
    return at(n);
  }
  template<typename T>
  const T& Mat<T, 2, 1>::at(usize n, usize m) const {
    return at(n);
  }

  //* Mat3x1 
  // (constructor)
  template<typename T>
  Mat<T, 3, 1>::Mat(T val)
    : x(val), y(val), z(val) {}
  template<typename T>
  Mat<T, 3, 1>::Mat(T x, T y, T z)
    : x(x), y(y), z(z) {}
  template<typename T>
  Mat<T, 3, 1>::Mat(const Mat<T, 2, 1>& xy, T z)
    : x(xy.x), y(xy.y), z(z) {}
  template<typename T>
  Mat<T, 3, 1>::Mat(T x, const Mat<T, 2, 1>& yz)
    : x(x), y(yz.x), z(yz.y) {}
  template<typename T>
  template<typename U, usize N>
  Mat<T, 3, 1>::Mat(const Mat<U, N, 1>& vec)
    : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)) {}
  template<typename T>
  template<typename U>
  Mat<T, 3, 1>::Mat(const Mat<U, 2, 1>& vec)
    : x(vec.at(0)), y(vec.at(1)), z(0) {}
  // at
  template<typename T>
  T& Mat<T, 3, 1>::at(usize index) {
    return index == 0 ? x : index == 1 ? y : z;
  }
  template<typename T>
  const T& Mat<T, 3, 1>::at(usize index) const {
    return index == 0 ? x : index == 1 ? y : z;
  }
  template<typename T>
  T& Mat<T, 3, 1>::at(usize n, usize m) {
    return Mat<T, 3, 1>::at(n);
  }
  template<typename T>
  const T& Mat<T, 3, 1>::at(usize n, usize m) const {
    return at(n);
  }

  //* Mat4x1
  // (constructor)
  template<typename T>
  Mat<T, 4, 1>::Mat(T val)
    : x(val), y(val), z(val), w(val) {}
  template<typename T>
  Mat<T, 4, 1>::Mat(T x, T y, T z, T w)
    : x(x), y(y), z(z), w(w) {}
  template<typename T>
  Mat<T, 4, 1>::Mat(const Mat<T, 2, 1>& xy, T z, T w)
    : x(xy.x), y(xy.y), z(z), w(w) {}
  template<typename T>
  Mat<T, 4, 1>::Mat(T x, const Mat<T, 2, 1>& yz, T w)
    : x(x), y(yz.x), z(yz.y), w(w) {}
  template<typename T>
  Mat<T, 4, 1>::Mat(T x, T y, const Mat<T, 2, 1>& zw)
    : x(x), y(y), z(zw.x), w(zw.y) {}
  template<typename T>
  Mat<T, 4, 1>::Mat(const Mat<T, 3, 1>& xyz, T w)
    : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
  template<typename T>
  Mat<T, 4, 1>::Mat(T x, const Mat<T, 3, 1>& yzw)
    : x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}
  template<typename T>
  template<typename U, usize N>
  Mat<T, 4, 1>::Mat(const Mat<U, N, 1>& vec)
    : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)), w(vec.at(3)) {}
  template<typename T>
  template<typename U>
  Mat<T, 4, 1>::Mat(const Mat<U, 2, 1>& vec)
    : x(vec.at(0)), y(vec.at(1)), z(0), w(0) {}
  template<typename T>
  template<typename U, usize N>
  Mat<T, 4, 1>::Mat(const Mat<U, 3, 1>& vec)
    : x(vec.at(0)), y(vec.at(1)), z(vec.at(2)), w(0) {}
  // at
  template<typename T>
  T& Mat<T, 4, 1>::at(usize index) {
    return index == 0 ? x : index == 1 ? y : index == 2 ? z : w;
  }
  template<typename T>
  const T& Mat<T, 4, 1>::at(usize index) const {
    return index == 0 ? x : index == 1 ? y : index == 2 ? z : w;
  }
  template<typename T>
  T& Mat<T, 4, 1>::at(usize n, usize m) {
    return at(n);
  }
  template<typename T>
  const T& Mat<T, 4, 1>::at(usize n, usize m) const {
    return at(n);
  }

  // zeros
  template<typename T, usize N, usize M>
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
  template<typename T, usize N, usize M>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat) {
    Mat<T, N, M> out;
    for (usize i = 0; i < N * M; ++i) {
      out.at(i) = -mat.at(i);
    }
    return out;
  }
  // +=
  template<typename T, usize N, usize M>
  Mat<T, N, M>& operator+=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) += other.at(i);
    }
    return mat;
  }
  // -=
  template<typename T, usize N, usize M>
  Mat<T, N, M>& operator-=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) -= other.at(i);
    }
    return mat;
  }
  // *=
  template<typename T, usize N, usize M>
  Mat<T, N, M>& operator*=(Mat<T, N, M>& mat, T scalar) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) *= scalar;
    }
    return mat;
  }
  // /=
  template<typename T, usize N, usize M>
  Mat<T, N, M>& operator/=(Mat<T, N, M>& mat, T scalar) {
    for (usize i = 0; i < N * M; ++i) {
      mat.at(i) /= scalar;
    }
    return mat;
  }

  // +
  template<typename T, usize N, usize M>
  Mat<T, N, M> operator+(const Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    Mat<T, N, M> out(mat);
    out += other;
    return out;
  }
  // -
  template<typename T, usize N, usize M>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
    Mat<T, N, M> out(mat);
    out -= other;
    return out;
  }
  // * (scalar)
  template<typename T, usize N, usize M>
  Mat<T, N, M> operator*(const Mat<T, N, M>& mat, T scalar) {
    Mat<T, N, M> out(mat);
    out *= scalar;
    return out;
  }
  // / (scalar)
  template<typename T, usize N, usize M>
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
  template<typename T, usize N, usize M>
  T dot(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
    T out = 0;
    for (usize i = 0; i < N * M; ++i) {
      out += mat1.at(i) * mat2.at(i);
    }
    return out;
  }
  // cross
  template<typename T>
  Mat<T, 3, 1> cross(const Mat<T, 3, 1>& v1, const Mat<T, 3, 1>& v2) {
    return {
      v1.z * v2.y - v1.y * v2.z,
      v1.x * v2.z - v1.z * v2.x,
      v1.y * v2.x - v1.x * v2.y,
    };
  }
  // magnitude
  template<typename T, usize N, usize M>
  T magnitude(const Mat<T, N, M>& mat) {
    return std::sqrt(dot(mat, mat));
  }
  // length
  template<typename T, usize N, usize M>
  T length(const Mat<T, N, M>& mat) {
    return magnitude(mat);
  }
  // dist
  template<typename T, usize N, usize M>
  T dist(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
    return length(mat2 - mat1);
  }

  // normalize(d)
  template<typename T, usize N, usize M>
  Mat<T, N, M>& normalize(Mat<T, N, M>& mat) {
    return mat /= length(mat);
  }
  template<typename T, usize N, usize M>
  Mat<T, N, M> normalized(const Mat<T, N, M>& mat) {
    return mat / length(mat);
  }

  // transpose(d)
  template<typename T, usize N>
  Mat<T, N>& transpose(Mat<T, N>& mat) {
    for (usize n1 = 0; n1 < N; ++n1) {
      for (usize n2 = 0; n2 < n1; ++n2) {
        T temp = mat.at(n1, n2);
        mat.at(n1, n2) = mat.at(n2, n1);
        mat.at(n2, n1) = temp;
      }
    }
    return mat;
  }
  template<typename T, usize N, usize M>
  Mat<T, M, N> transposed(const Mat<T, N, M>& mat) {
    Mat<T, M, N> out;
    for (usize n = 0; n < N; ++n) {
      for (usize m = 0; m < M; ++m) {
        out.at(m, n) = mat.at(n, m);
      }
    }
    return out;
  }

  // insert
  template<typename T, usize N1, usize M1, usize N2, usize M2>
  Mat<T, N1, M1>& insert(
    Mat<T, N1, M1>& dest, const Mat<T, N2, M2>& src,
    Mat<uint, 2, 1> origin
  ) {
    for (usize n = 0; n < min(N1 - origin.x, N2); ++n) {
      for (usize m = 0; m < min(M1 - origin.y, M2); ++m) {
        dest.at(origin.x + n, origin.y + m) = src.at(n, m);
      }
    }
    return dest;
  }
  // resize
  template<usize N1, usize M1, typename T, usize N2, usize M2>
  Mat<T, N1, M1> resize(
    const Mat<T, N2, M2>& mat, const Mat<uint, 2, 1>& origin
  ) {
    Mat<T, N1, M1> out = zeros<T, N1, M1>();
    insert(out, mat, origin);
    return out;
  }

  // << (stream)
  template<typename T, usize N, usize M>
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
}