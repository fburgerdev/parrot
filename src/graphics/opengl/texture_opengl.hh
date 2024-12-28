#pragma once
#include "graphics/texture_config.hh"

namespace Parrot {
	namespace OpenGL {
		// Texture
		class Texture {
		public:
			// Texture / ~Texture
			Texture(const TextureConfig& config, AssetHandleResolver resolver);
			Texture(const Texture&) = delete;
			Texture(Texture&& other) noexcept;
			~Texture();
			// =
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