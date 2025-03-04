#pragma once
#include "texture_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    // FrameBuffer
    class FrameBuffer {
    public:
      // (constructor)
      FrameBuffer(uint width, uint height);
      FrameBuffer(const FrameBuffer&) = delete;
      FrameBuffer(FrameBuffer&& other) noexcept;
      // (destructor)
      ~FrameBuffer();
      // (assignment)
      FrameBuffer& operator=(const FrameBuffer&) = delete;
      FrameBuffer& operator=(FrameBuffer&& other) noexcept;

      // getTexture
      const Texture& getTexture() const;

      // bind / unbind
      void bind() const;
      static void unbind();
    private:
      uint _gpu_id = 0, _depth_stencil_id = 0;
      Texture _texture;
    };
  }
}