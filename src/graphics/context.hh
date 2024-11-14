#pragma once
#include "shader.hh"
#include "texture.hh"

#if defined(PARROT_OPENGL)
#include "opengl/shader_opengl.hh"
#include "opengl/texture_opengl.hh"
namespace Parrot {
	using GPUShader = ShaderOpenGL;
	using GPUTexture = TextureOpenGL;
}
#endif

namespace Parrot {
	// GPUContext
	class GPUContext {
	private:
		HashMap<Shader*, GPUShader> _shader_map;
		HashMap<Texture*, GPUTexture> _texture_map;
	};
}