#pragma once

namespace Parrot {
  namespace OpenGL {
    constexpr usize roundToBaseAlign(usize offset, usize base_align) {
      if (base_align > 0 && offset % base_align) {
        return (offset / base_align + 1) * base_align;
      }
      return offset;
    }

    template<class T>
    void setSTD140(Vec2<T> vec, List<uchar>::iterator it) {
      setSTD140(vec.x, it + SIZE_STD140<T> *0);
      setSTD140(vec.y, it + SIZE_STD140<T> *1);
    }
    template<class T>
    void setSTD140(Vec3<T> vec, List<uchar>::iterator it) {
      setSTD140(vec.x, it + SIZE_STD140<T> *0);
      setSTD140(vec.y, it + SIZE_STD140<T> *1);
      setSTD140(vec.z, it + SIZE_STD140<T> *2);
    }
    template<class T>
    void setSTD140(Vec4<T> vec, List<uchar>::iterator it) {
      setSTD140(vec.x, it + SIZE_STD140<T> *0);
      setSTD140(vec.y, it + SIZE_STD140<T> *1);
      setSTD140(vec.z, it + SIZE_STD140<T> *2);
      setSTD140(vec.w, it + SIZE_STD140<T> *3);
    }
    template<class T, usize N>
    void setSTD140(const Array<T, N>& arr, List<uchar>::iterator it) {
      for (usize i = 0; i < N; ++i) {
        setSTD140(arr.at(i), it + roundToBaseAlign(SIZE_STD140<T>) * i);
      }
    }
    template<class T, usize N, usize M>
    void setSTD140(const Mat<T, N, M>& mat, List<uchar>::iterator it) {
      for (usize m = 0; m < M; ++m) {
        for (usize n = 0; n < N; ++n) {
          usize offset = BASE_ALIGN_STD140<Mat<T, N, M>>* m;
          offset += SIZE_STD140<T> *n;
          setSTD140(mat.at(n, m), it + offset);
        }
      }
    }
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