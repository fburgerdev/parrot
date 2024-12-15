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
	inline void prepareDrawGPU() {
		prepareDrawOpenGL();
	}
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
		void use(const Sidecar<Mesh>& mesh, const Transform<>& transform);
		void use(const Material& material, const Camera& camera, const Transform<>& camera_transform);
		// prepareDraw
		void prepareDraw();
		// draw
		void draw(usize count);
		
		// friend: PlayingUnit
		friend class PlayingUnit;
	private:
		GPUContext(HandleResolver resolver);
		//TODO: fix access violation caused by moving window
		//GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver);
		// applyMaterial
		void applyMaterial(GPUShader& shader, const MaterialNode& node, const string& prefix = "");

		function<void()> _bind, _unbind;
		GPUMesh* _current_mesh = nullptr;
		GPUShader* _current_shader = nullptr;
		HashMap<uuid, GPUMesh> _meshes;
		HashMap<uuid, GPUShader> _shaders;
		HashMap<uuid, GPUTexture> _textures;
		HandleResolver _resolver;
	};
}