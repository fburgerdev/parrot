#pragma once
#include "mesh.hh"
#include "material.hh"
#include "shader.hh"
#include "texture.hh"
#include "camera.hh"
#include "math/3d.hh"
#if defined(PARROT_OPENGL)
#include "opengl/mesh_opengl.hh"
#include "opengl/shader_opengl.hh"
#include "opengl/texture_opengl.hh"
#include "opengl/draw_opengl.hh"
namespace Parrot {
	using GPUMesh = MeshOpenGL;
	using GPUShader = ShaderOpenGL;
	using GPUTexture = TextureOpenGL;
	inline void drawGPU(usize count) {
		drawOpenGL(count);
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
		void use(const Mesh& mesh, const Transform<>& transform);
		void use(const Material& material, const Camera& camera, const Transform<>& camera_transform);
		// draw
		void draw(usize count);
		
		// friend: PlayingUnit
		friend class PlayingUnit;
	private:
		GPUContext(HandleResolver resolver);
		GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver);

		function<void()> _bind, _unbind;
		GPUShader* _current_shader = nullptr;
		HashMap<uuid, GPUMesh> _meshes;
		HashMap<uuid, GPUShader> _shaders;
		HashMap<uuid, GPUTexture> _textures;
		HandleResolver _resolver;
	};
}