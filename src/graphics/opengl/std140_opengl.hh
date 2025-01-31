#pragma once
#include "math/matrix.hh"

namespace Parrot {
  namespace OpenGL {
    // roundToBaseAlign
    constexpr usize roundToBaseAlign(usize offset, usize base_align = 16) {
      if (base_align > 0 && offset % base_align) {
        return (offset / base_align + 1) * base_align;
      }
      return offset;
    }

    // BASE_ALIGN_STD140
    template<class T>
    constexpr usize BASE_ALIGN_STD140 = 0;
    // SIZE_STD140
    template<class T>
    constexpr usize SIZE_STD140 = 0;

    // STRUCT_OFFSET_STD140
    template<usize Index, class... Types>
    constexpr usize STRUCT_OFFSET_STD140 = (
      roundToBaseAlign(
        STRUCT_OFFSET_STD140<Index - 1, Types...> +
        SIZE_STD140<std::tuple_element_t<Index - 1, Tuple<Types...>>>,
        BASE_ALIGN_STD140<std::tuple_element_t<Index, Tuple<Types...>>>
      )
    );
    template<class... Types>
    constexpr usize STRUCT_OFFSET_STD140<0, Types...> = 0;

    // BASE_ALIGN_STD140
    template<>
    constexpr usize BASE_ALIGN_STD140<bool> = 4;
    template<>
    constexpr usize BASE_ALIGN_STD140<int32> = 4;
    template<>
    constexpr usize BASE_ALIGN_STD140<uint32> = 4;
    template<>
    constexpr usize BASE_ALIGN_STD140<float32> = 4;
    template<>
    constexpr usize BASE_ALIGN_STD140<float64> = 8;
    template<class T>
    constexpr usize BASE_ALIGN_STD140<Vec2<T>> = BASE_ALIGN_STD140<T> * 2;
    template<class T>
    constexpr usize BASE_ALIGN_STD140<Vec3<T>> = BASE_ALIGN_STD140<T> * 4;
    template<class T>
    constexpr usize BASE_ALIGN_STD140<Vec4<T>> = BASE_ALIGN_STD140<T> * 4;
    template<class T, usize N>
    constexpr usize BASE_ALIGN_STD140<Array<T, N>> = (
      roundToBaseAlign(BASE_ALIGN_STD140<T>)
    );
    template<class T, usize N, usize M>
    constexpr usize BASE_ALIGN_STD140<Mat<T, N, M>> = (
      roundToBaseAlign(BASE_ALIGN_STD140<T> * N)
    );
    template<class... Types>
    constexpr usize BASE_ALIGN_STD140<Tuple<Types...>> = (
      roundToBaseAlign(max(BASE_ALIGN_STD140<Types>...))
    );
    // SIZE_STD140
    template<>
    constexpr usize SIZE_STD140<bool> = 4;
    template<>
    constexpr usize SIZE_STD140<int32> = 4;
    template<>
    constexpr usize SIZE_STD140<uint32> = 4;
    template<>
    constexpr usize SIZE_STD140<float32> = 4;
    template<>
    constexpr usize SIZE_STD140<float64> = 8;
    template<class T>
    constexpr usize SIZE_STD140<Vec2<T>> = SIZE_STD140<T> * 2;
    template<class T>
    constexpr usize SIZE_STD140<Vec3<T>> = SIZE_STD140<T> * 3;
    template<class T>
    constexpr usize SIZE_STD140<Vec4<T>> = SIZE_STD140<T> * 4;
    template<class T, usize N>
    constexpr usize SIZE_STD140<Array<T, N>> = (
      roundToBaseAlign(SIZE_STD140<T>) * N
    );
    template<class T, usize N, usize M>
    constexpr usize SIZE_STD140<Mat<T, N, M>> = (
      roundToBaseAlign(SIZE_STD140<T> * N) * M
    );
    template<class... Types>
    constexpr usize SIZE_STD140<Tuple<Types...>> =
      STRUCT_OFFSET_STD140<sizeof...(Types) - 1, Types...> +
      SIZE_STD140<std::tuple_element_t<sizeof...(Types) - 1, Tuple<Types...>>>;

    // setSTD140
    void setSTD140(bool x, List<uchar>::iterator it);
    void setSTD140(int32 x, List<uchar>::iterator it);
    void setSTD140(uint32 x, List<uchar>::iterator it);
    void setSTD140(float32 x, List<uchar>::iterator it);
    void setSTD140(float64 x, List<uchar>::iterator it);
    template<class T>
    void setSTD140(Vec2<T> vec, List<uchar>::iterator it);
    template<class T>
    void setSTD140(Vec3<T> vec, List<uchar>::iterator it);
    template<class T>
    void setSTD140(Vec4<T> vec, List<uchar>::iterator it);
    template<class T, usize N, usize M>
    void setSTD140(const Mat<T, N, M>& mat, List<uchar>::iterator it);
    template<class T, usize N>
    void setSTD140(const Array<T, N>& arr, List<uchar>::iterator it);
    template<class... Types>
    void setSTD140(const Tuple<Types...>& tuple, List<uchar>::iterator it);
    // :: vec
    template<class T>
    void setSTD140(Vec2<T> vec, List<uchar>::iterator it) {
      setSTD140(vec.x, it + SIZE_STD140<T> * 0);
      setSTD140(vec.y, it + SIZE_STD140<T> * 1);
    }
    template<class T>
    void setSTD140(Vec3<T> vec, List<uchar>::iterator it) {
      setSTD140(vec.x, it + SIZE_STD140<T> * 0);
      setSTD140(vec.y, it + SIZE_STD140<T> * 1);
      setSTD140(vec.z, it + SIZE_STD140<T> * 2);
    }
    template<class T>
    void setSTD140(Vec4<T> vec, List<uchar>::iterator it) {
      setSTD140(vec.x, it + SIZE_STD140<T> * 0);
      setSTD140(vec.y, it + SIZE_STD140<T> * 1);
      setSTD140(vec.z, it + SIZE_STD140<T> * 2);
      setSTD140(vec.w, it + SIZE_STD140<T> * 3);
    }
    // :: arr
    template<class T, usize N>
    void setSTD140(const Array<T, N>& arr, List<uchar>::iterator it) {
      for (usize i = 0; i < N; ++i) {
        setSTD140(arr.at(i), it + roundToBaseAlign(SIZE_STD140<T>) * i);
      }
    }
    // :: mat
    /*
      Note that we need to transpose the matrix since opengl is column-major
    */
    template<class T, usize N, usize M>
    void setSTD140(const Mat<T, N, M>& mat, List<uchar>::iterator it) {
      for (usize m = 0; m < M; ++m) {
        for (usize n = 0; n < N; ++n) {
          usize offset = BASE_ALIGN_STD140<Mat<T, N, M>> * m;
          offset += SIZE_STD140<T> * n;
          setSTD140(mat.at(n, m), it + offset);
        }
      }
    }
    // :: struct
    template<usize Index, class... Types>
    void setSTD140(const Tuple<Types...>& tuple, List<uchar>::iterator it) {
      if constexpr (Index < sizeof...(Types)) {
        setSTD140(
          std::get<Index>(tuple), it + STRUCT_OFFSET_STD140<Index, Types...>
        );
        setSTD140<Index + 1>(tuple, it);
      }
    }
    template<class... Types>
    void setSTD140(const Tuple<Types...>& tuple, List<uchar>::iterator it) {
      setSTD140<0>(tuple, it);
    }

    // createSTD140
    template<class T>
    List<uchar> createSTD140(const T& value) {
      List<uchar> out(SIZE_STD140<T>);
      for (usize i = 0; i < out.size(); ++i) {
        out.at(i) = uchar(i);
      }
      setSTD140(value, out.begin());
      return out;
    }
  }
}