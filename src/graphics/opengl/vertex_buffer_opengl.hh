#pragma once
#include "common.hh"

namespace Parrot {
  namespace OpenGL {
    class VertexBuffer {
    public:
      VertexBuffer(usize size);
      VertexBuffer(const void* buffer, usize size);
      VertexBuffer(const VertexBuffer&) = delete;
      VertexBuffer(VertexBuffer&& other) noexcept;
      ~VertexBuffer();
      VertexBuffer& operator=(const VertexBuffer&) = delete;
      VertexBuffer& operator=(VertexBuffer&& other) noexcept;

      void overwriteData(const void* buffer, usize size, usize offset = 0);

      void bind() const;
      static void unbind();
    private:
      uint _gpu_id = 0;
      bool _is_static;
    };
  }
}