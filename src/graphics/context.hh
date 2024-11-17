#pragma once
#include "mesh.hh"
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
	public:
		// getShader
		GPUShader& getShader(const Shader& shader);
		// getTexture
		GPUTexture& getTexture(const Texture& texture);
		void draw();

		// friend
		friend class GPU;
	private:
		GPUContext(function<void()>&& bind, function<void()>&& unbind);

		function<void()> _bind, _unbind;
		HashMap<const Shader*, GPUShader> _shaders;
		HashMap<const Texture*, GPUTexture> _textures;
	};
}