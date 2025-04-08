#pragma once
#include "graphics/render_data.hh"
#include "graphics/shader_source.hh"
#include "std140_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    // MAX_LIGHT_COUNT
    //! This must match with MAX_LIGHT_COUNT in ".parrot/surface.glsl.macro"
    constexpr uint MAX_LIGHT_COUNT = 50;

    // SurfaceBlock
    struct SurfaceBlock {
      // (constructor)
      SurfaceBlock();

      // set
      void set(const RenderData& render_data);

      // getSize
      usize getSize() const;
      // getBuffer
      const uchar* getBuffer() const;
    private:
      template<usize N, class T>
      static Array<T, N> embedList(const List<T>& list);

      List<uchar> _bytes;
    };
  }
}
#include "surface_opengl_impl.hh"