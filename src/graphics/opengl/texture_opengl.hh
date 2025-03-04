#pragma once
#include "graphics/texture_config.hh"

namespace Parrot {
  namespace OpenGL {
    // Texture
    class Texture {
    public:
      // (constructor)
      Texture(uint width, uint height);
      Texture(const TextureConfig& config);
      Texture(const Texture&) = delete;
      Texture(Texture&& other) noexcept;
      // (destructor)
      ~Texture();
      // (assignment)
      Texture& operator=(const Texture&) = delete;
      Texture& operator=(Texture&& other) noexcept;

      // bind, unbind
      void bind(uint slot) const;
      static void unbind(uint slot);

      // friend
      friend class FrameBuffer;
    private:
      uint _gpu_id = 0;
    };
  }
}