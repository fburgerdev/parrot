#pragma once
#include "graphics/texture.hh"

namespace Parrot {
	// TextureOpenGL
	class TextureOpenGL {
	public:
		// ShaderOpenGL
		TextureOpenGL(const Texture& texture);
		// bind, unbind
		void bind();
		static void unbind();
	};
}