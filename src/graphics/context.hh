#pragma once
#include "mesh.hh"
#include "material.hh"
#include "shader.hh"
#include "texture.hh"

#if defined(PARROT_OPENGL)
#include "opengl/shader_opengl.hh"
#include "opengl/texture_opengl.hh"
#include "opengl/draw_opengl.hh"
namespace Parrot {
	using GPUShader = ShaderOpenGL;
	using GPUTexture = TextureOpenGL;
	inline void drawGPU() {
		drawOpenGL();
	}
}
#endif

namespace Parrot {
	// GPUContext
	class GPUContext {
	public:
		// GPUContext
		GPUContext() = default;

		// use
		void use(const Mesh& mesh);
		void use(const Material& material);
		// draw
		void draw();
		
		// friend: PlayingUnit
		friend class PlayingUnit;
	private:
		GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver);

		function<void()> _bind, _unbind;
		HashMap<const Shader*, GPUShader> _shaders;
		HashMap<const Texture*, GPUTexture> _textures;
		HandleResolver _resolver;
	};
}