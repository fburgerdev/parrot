#pragma once
#include "common.hh"

namespace Parrot {
  namespace OpenGL {
    class IndexBuffer {
    public:
      IndexBuffer(usize count);
      IndexBuffer(const uint32* indices, usize count);
      IndexBuffer(const IndexBuffer&) = delete;
      IndexBuffer(IndexBuffer&& other) noexcept;
      ~IndexBuffer();
      IndexBuffer& operator=(const IndexBuffer&) = delete;
      IndexBuffer& operator=(IndexBuffer&& other) noexcept;

      void overwriteData(const uint32* indices, usize count, usize index = 0);

      void bind() const;
      static void unbind();
    private:
      uint _gpu_id = 0;
      bool _is_static;
    };
  }
}