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
}
#include "math_matrix_impl.hh"