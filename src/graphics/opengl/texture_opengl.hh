#pragma once
#include "graphics/texture_config.hh"

namespace Parrot {
	namespace OpenGL {
		// Texture
		class Texture {
		public:
			// (constructor)
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
		private:
			uint _gpu_id = 0;
		};
	}
}