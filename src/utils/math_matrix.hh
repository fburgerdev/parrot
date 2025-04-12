#pragma once
#include "math_basic.hh"

namespace Parrot {
  /// @brief Generic mathematical row-major matrix struct.
  /// @tparam T Type of matrix entries
  /// @tparam N Count of rows 
  /// @tparam M Count of columns
  template<typename T, usize N, usize M = N>
  struct Mat {
  public:
    /// @brief Type of matrix entries.
    using Type = T;
    static constexpr usize ROWS = N;
    static constexpr usize COLS = M;

    /// @note Entries are uninitialized
    Mat() = default;
    /// @tparam U Type of matrix entries, convertible to @c T
    template<typename U>
    Mat(const Mat<U, N, M>& mat);
    
    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    T& at(usize index);
    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    const T& at(usize index) const;
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    T& at(usize n, usize m);
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    const T& at(usize n, usize m) const;
    /// @brief Access buffer of all matrix entries in order.
    /// @return Pointer to buffer begin
    T* data();
    /// @brief Access buffer of all matrix entries in order.
    /// @return Pointer to buffer begin
    const T* data() const;

    /// @brief Lexicographically compare matrices.
    auto operator<=>(const Mat<T, N, M>&) const = default;
  private:
    Array<T, N * M> _array;
  };
  template<typename T>
  struct Mat<T, 2, 1> {
    /// @brief Type of matrix entries.
    using Type = T;
    static constexpr usize ROWS = 2;
    static constexpr usize COLS = 1;

    /// @note Entries are uninitialized
    Mat() = default;
    /// @brief Initialize all vector components with the same value.
    /// @param val Component value
    Mat(T val);
    /// @brief Initialize vector component-wise.
    Mat(T x, T y);
    /// @brief Initialize vector using the first 2 components of another vector.
    /// @tparam U Type of other vector components, convertible to @c T
    /// @tparam N Size of other vector
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec);

    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    T& at(usize index);
    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    const T& at(usize index) const;
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    T& at(usize n, usize m);
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    const T& at(usize n, usize m) const;
    
    /// @brief Lexicographically compare vectors.
    auto operator<=>(const Mat<T, 2, 1>&) const = default;

    /// @brief Vector components (x, y)
    T x, y;
  };
  template<typename T>
  struct Mat<T, 3, 1> {
    /// @brief Type of matrix entries.
    using Type = T;
    static constexpr usize ROWS = 3;
    static constexpr usize COLS = 1;

    /// @note Entries are uninitialized
    Mat() = default;
    /// @brief Initialize all vector components with the same value.
    /// @param val Component value
    Mat(T val);
    /// @brief Initialize vector component-wise.
    Mat(T x, T y, T z);
    /// @brief Initialize vector using vector components and values.
    Mat(const Mat<T, 2, 1>& xy, T z);
    /// @brief Initialize vector using vector components and values.
    Mat(T x, const Mat<T, 2, 1>& yz);
    /// @brief Initialize vector using the first 3 components of another vector.
    /// @tparam U Type of other vector components, convertible to @c T
    /// @tparam N Size of other vector
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec);
    template<typename U>
    /// @brief Initialize vector using the components of a 2-dimensional vector,
    /// and set @c z to 0.
    /// @tparam U Type of other vector components, convertible to @c T
    Mat(const Mat<U, 2, 1>& vec);
    
    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    T& at(usize index);
    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    const T& at(usize index) const;
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    T& at(usize n, usize m);
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    const T& at(usize n, usize m) const;
    
    /// @brief Lexicographically compare vectors.
    auto operator<=>(const Mat<T, 3, 1>&) const = default;
    
    /// @brief Vector components (x, y, z)
    T x, y, z;
  };
  template<typename T>
  struct Mat<T, 4, 1> {
    /// @brief Type of matrix entries.
    using Type = T;
    static constexpr usize ROWS = 4;
    static constexpr usize COLS = 1;

    /// @note Entries are uninitialized
    Mat() = default;
    /// @brief Initialize all vector components with the same value.
    /// @param val Component value
    Mat(T val);
    /// @brief Initialize vector component-wise.
    Mat(T x, T y, T z, T w);
    /// @brief Initialize vector using vector components and values.
    Mat(const Mat<T, 2, 1>& xy, T z, T w);
    /// @brief Initialize vector using vector components and values.
    Mat(T x, const Mat<T, 2, 1>& yz, T w);
    /// @brief Initialize vector using vector components and values.
    Mat(T x, T y, const Mat<T, 2, 1>& zw);
    /// @brief Initialize vector using vector components and values.
    Mat(const Mat<T, 3, 1>& xyz, T w);
    Mat(T x, const Mat<T, 3, 1>& yzw);
    /// @brief Initialize vector using the first 4 components of another vector.
    /// @tparam U Type of other vector components, convertible to @c T
    /// @tparam N Size of other vector
    template<typename U, usize N>
    Mat(const Mat<U, N, 1>& vec);
    /// @brief Initialize vector using the components of a 2-dimensional vector,
    /// and set @c z and @c w to 0.
    /// @tparam U Type of other vector components, convertible to @c T
    template<typename U>
    Mat(const Mat<U, 2, 1>& vec);
    /// @brief Initialize vector using the components of a 3-dimensional vector,
    /// and set @c w to 0.
    /// @tparam U Type of other vector components, convertible to @c T
    template<typename U, usize N>
    Mat(const Mat<U, 3, 1>& vec);

    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    T& at(usize index);
    /// @brief Access entry at certain index.
    /// @param index = @c N * row + column 
    /// @return Reference to entry
    const T& at(usize index) const;
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    T& at(usize n, usize m);
    /// @brief Access entry at certain row and column.
    /// @param n Row of entry
    /// @param m Column of entry
    /// @return Reference to entry
    const T& at(usize n, usize m) const;
    
    /// @brief Lexicographically compare vectors.
    auto operator<=>(const Mat<T, 4, 1>&) const = default;

    /// @brief Vector components (x, y, z, w)
    T x, y, z, w;
  };

  /// @brief Create zero initialized matrix.
  /// @tparam T Type of the matrix entries
  /// @tparam N Count of rows
  /// @tparam M Count of columns
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> zeros();
  /// @brief Create identity matrix.
  /// @tparam T Type of the matrix entries
  /// @tparam N Count of rows and columns
  template<typename T, usize N>
  Mat<T, N> identity();

  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator+=(Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator-=(Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator*=(Mat<T, N, M>& mat, T scalar);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& operator/=(Mat<T, N, M>& mat, T scalar);

  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator+(const Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator-(const Mat<T, N, M>& mat, const Mat<T, N, M>& other);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator*(const Mat<T, N, M>& mat, T scalar);
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> operator/(const Mat<T, N, M>& mat, T scalar);
  template<typename T, usize N, usize M, usize L>
  Mat<T, N, L> operator*(const Mat<T, N, M>& mat1, const Mat<T, M, L>& mat2);
  template<typename T, usize N>
  Mat<T, N>& operator*=(Mat<T, N>& mat1, const Mat<T, N>& mat2);

  /// @brief Calculate the component-wise products and sum them up.
  template<typename T, usize N, usize M = N>
  T dot(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2);
  /// @brief The mathematical cross-product of two 3-dimensional vectors
  /// @note The resulting normal vectors orientation can be determined using,
  /// the right-hand-rule
  template<typename T>
  Mat<T, 3, 1> cross(const Mat<T, 3, 1>& v1, const Mat<T, 3, 1>& v2);
  /// @brief Calculate the square root of the dot-product with itself.
  template<typename T, usize N, usize M = N>
  T magnitude(const Mat<T, N, M>& mat);
  /// @brief Calculate the square root of the dot-product with itself.
  template<typename T, usize N, usize M = N>
  T length(const Mat<T, N, M>& mat);
  /// @brief Calculate the magnitude of the difference of the two matrices.
  template<typename T, usize N, usize M = N>
  T dist(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2);

  /// @brief Divide matrix by its length, so that its resulting length is 1.
  /// @return Reference to @c mat
  template<typename T, usize N, usize M = N>
  Mat<T, N, M>& normalize(Mat<T, N, M>& mat);
  /// @brief Divide matrix by its length, so that its resulting length is 1.
  template<typename T, usize N, usize M = N>
  Mat<T, N, M> normalized(const Mat<T, N, M>& mat);

  /// @brief Flip matrix by swapping rows and columns ((i, j) -> (j, i))
  /// @return Reference to @c mat
  template<typename T, usize N>
  Mat<T, N>& transpose(Mat<T, N>& mat);
  /// @brief Flip matrix by swapping rows and columns ((i, j) -> (j, i))
  template<typename T, usize N, usize M = N>
  Mat<T, M, N> transposed(const Mat<T, N, M>& mat);

  /// @brief Insert smaller matrix into a bigger one.
  /// @param dest Bigger matrix to insert into
  /// @param src Smaller matrix to insert from
  /// @param origin Top-left coordinates where the matrix should be inserted
  template<typename T, usize N1, usize M1, usize N2, usize M2>
  Mat<T, N1, M1>& insert(
    Mat<T, N1, M1>& dest, const Mat<T, N2, M2>& src,
    Mat<uint, 2, 1> origin = { 0, 0 }
  );
  /// @brief Extend matrix to more dimensions and fill them with zeros.
  /// @param mat Matrix to resize
  /// @param origin Top-left coordinates where the matrix should be inserted
  template<usize N1, usize M1, typename T, usize N2, usize M2>
  Mat<T, N1, M1> resize(
    const Mat<T, N2, M2>& mat, const Mat<uint, 2, 1>& origin = { 0, 0 }
  );
  /// @brief Stream matrix.
  template<typename T, usize N, usize M = N>
  ostream& operator<<(ostream& stream, const Mat<T, N, M>& mat);

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
  template<typename T, usize N>
  using Vec = Mat<T, N, 1>;
  template<typename T = DefaultFloat>
  using Vec2 = Vec<T, 2>;
  template<typename T = DefaultFloat>
  using Vec3 = Vec<T, 3>;
  template<typename T = DefaultFloat>
  using Vec4 = Vec<T, 4>;
  using Vec2i = Vec2<int>;
  using Vec3i = Vec3<int>;
  using Vec4i = Vec4<int>;
  using Vec2u = Vec2<uint>;
  using Vec3u = Vec3<uint>;
  using Vec4u = Vec4<uint>;
  using Vec2f = Vec2<float>;
  using Vec3f = Vec3<float>;
  using Vec4f = Vec4<float>;
  using Vec2d = Vec2<double>;
  using Vec3d = Vec3<double>;
  using Vec4d = Vec4<double>;
}
#include "math_matrix_impl.hh"