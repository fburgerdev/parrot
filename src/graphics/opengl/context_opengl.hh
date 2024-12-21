#pragma once
#include "graphics/mesh.hh"
#include "graphics/material.hh"
#include "mesh_opengl.hh"
#include "shader_opengl.hh"
#include "texture_opengl.hh"
#include "math/3d.hh"
#include "graphics/camera.hh"
#include "graphics/light_source.hh"
#include "graphics/render_object.hh"

namespace Parrot {
	// ContextOpenGL
	class ContextOpenGL {
	public:
		// ContextOpenGL
		ContextOpenGL(HandleResolver resolver);

		// getMesh
		MeshOpenGL& getMesh(const Sidecar<Mesh>& mesh);
		// getShader
		ShaderOpenGL& getShader(const ShaderProgram& shader);
		// getTexture
		TextureOpenGL& getTexture(const Texture& texture);

		// createVertexBuffer
		template<class... Args>
		VertexBufferOpenGL& createVertexBuffer(Args&&... args) {
			return _vertex_buffers.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
		}
		// createIndexBuffer
		template<class... Args>
		IndexBufferOpenGL& createIndexBuffer(Args&&... args) {
			return _index_buffers.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
		}
		// createUniformBuffer
		template<class... Args>
		UniformBufferOpenGL& createUniformBuffer(Args&&... args) {
			return _uniform_buffers.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
		}
		// createVertexArray
		template<class... Args>
		VertexArrayOpenGL& createVertexArray(Args&&... args) {
			return _vertex_arrays.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
		}

		// applyMaterial
		void applyMaterial(ShaderOpenGL& shader, const MaterialNode& node, const string& prefix = "");
	private:
		HashMap<uuid, MeshOpenGL> _meshes;
		HashMap<uuid, ShaderOpenGL> _shaders;
		HashMap<uuid, TextureOpenGL> _textures;
		HashMap<uuid, VertexBufferOpenGL> _vertex_buffers;
		HashMap<uuid, IndexBufferOpenGL> _index_buffers;
		HashMap<uuid, UniformBufferOpenGL> _uniform_buffers;
		HashMap<uuid, VertexArrayOpenGL> _vertex_arrays;
		HandleResolver _resolver;
	};
}