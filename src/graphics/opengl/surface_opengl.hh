#pragma once
#include "graphics/render_data.hh"
#include "graphics/shader_source.hh"
#include "std140_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    constexpr uint MAX_LIGHT_COUNT = 50;

    struct SurfaceBlock {
      SurfaceBlock();

      void set(const RenderData& render_data);

      usize getSize() const;
      const uchar* getBuffer() const;
    private:
      template<usize N, class T>
      static Array<T, N> embedList(const List<T>& list);

      List<uchar> _bytes;
    };
  }
}
#include "surface_opengl_impl.hh"