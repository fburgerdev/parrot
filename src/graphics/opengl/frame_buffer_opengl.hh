#pragma once
#include "texture_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    class FrameBuffer {
    public:
      FrameBuffer(uint width, uint height);
      FrameBuffer(const FrameBuffer&) = delete;
      FrameBuffer(FrameBuffer&& other) noexcept;
      ~FrameBuffer();
      FrameBuffer& operator=(const FrameBuffer&) = delete;
      FrameBuffer& operator=(FrameBuffer&& other) noexcept;

      const Texture& getTexture() const;
      const Texture& getDepthTexture() const;

      void bind() const;
      static void unbind();
    private:
      uint _gpu_id = 0;
      Texture _texture, _depth;
    };
  }
}