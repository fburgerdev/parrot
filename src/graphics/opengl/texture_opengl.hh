#pragma once
#include "graphics/guard.hh"
#include "graphics/texture.hh"

namespace Parrot {
	// TextureOpenGL
	class TextureOpenGL {
	public:
		// ShaderOpenGL
		TextureOpenGL(const Texture& texture, ContextGuard&& guard);
	};
}