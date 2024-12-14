#pragma once
#include "graphics/texture.hh"

namespace Parrot {
	// TextureOpenGL
	class TextureOpenGL {
	public:
		// TextureOpenGL / ~TextureOpenGL
		TextureOpenGL(const Texture& texture, HandleResolver resolver);
		TextureOpenGL(const TextureOpenGL&) = delete;
		TextureOpenGL(TextureOpenGL&& other) noexcept;
		~TextureOpenGL();
		// =
		TextureOpenGL& operator=(const TextureOpenGL&) = delete;
		TextureOpenGL& operator=(TextureOpenGL&& other) noexcept;

		// bind, unbind
		void bind(uint slot) const;
		static void unbind(uint slot);
	private:
		uint _gpu_id = 0;
	};
}