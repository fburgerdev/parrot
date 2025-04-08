#pragma once

namespace Parrot {
  namespace OpenGL {
    // embedList
    template<usize N, class T>
    Array<T, N> SurfaceBlock::embedList(const List<T>& list) {
      Array<T, N> out;
      for (usize i = 0; i < list.size(); ++i) {
        out.at(i) = list.at(i);
      }
      return out;
    }
  }
}