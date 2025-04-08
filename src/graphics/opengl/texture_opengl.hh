#pragma once
#include "graphics/texture_config.hh"

namespace Parrot {
  namespace OpenGL {
    enum class TextureFormat {
      RGBA, DEPTH
    };
    class Texture {
    public:
      Texture(uint width, uint height, TextureFormat format);
      Texture(const TextureConfig& config);
      Texture(const Texture&) = delete;
      Texture(Texture&& other) noexcept;
      ~Texture();
      Texture& operator=(const Texture&) = delete;
      Texture& operator=(Texture&& other) noexcept;

      void bind(uint slot) const;
      static void unbind(uint slot);

      friend class FrameBuffer;
    private:
      uint _gpu_id = 0;
    };
  }
}