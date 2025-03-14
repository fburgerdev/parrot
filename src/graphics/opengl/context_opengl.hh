#pragma once
#include "graphics/camera.hh"
#include "graphics/light.hh"
#include "graphics/render_object.hh"
#include "graphics/material.hh"
#include "frame_buffer_opengl.hh"
#include "vertex_array_opengl.hh"
#include "shader_opengl.hh"
#include "texture_opengl.hh"
#include "utils/math_3d.hh"

namespace Parrot {
  namespace OpenGL {
    // Context
    class Context {
    public:
      // (constructor)
      Context(AssetAPI& api);

      // getFrameBuffer
      FrameBuffer& getFrameBuffer(usize index);
      FrameBuffer& getFrameBuffer(const string& name);

      // getVertexArray
      VertexArray& getVertexArray(const Mesh& mesh);
      // getShader
      Shader& getShader(const ShaderProgram& program);
      // getTexture
      Texture& getTexture(const TextureConfig& texture);

      // createVertexBuffer
      template<class... Args>
      VertexBuffer& createVertexBuffer(Args&&... args) {
        return _vertex_buffers.try_emplace(
          generateUUID(), std::forward<Args>(args)...
        ).first->second;
      }
      // createIndexBuffer
      template<class... Args>
      IndexBuffer& createIndexBuffer(Args&&... args) {
        return _index_buffers.try_emplace(
          generateUUID(), std::forward<Args>(args)...
        ).first->second;
      }
      // createUniformBuffer
      template<class... Args>
      UniformBuffer& createUniformBuffer(Args&&... args) {
        return _uniform_buffers.try_emplace(
          generateUUID(), std::forward<Args>(args)...
        ).first->second;
      }
      // createVertexArray
      template<class... Args>
      VertexArray& createVertexArray(Args&&... args) {
        return _vertex_arrays.try_emplace(
          generateUUID(), std::forward<Args>(args)...
        ).first->second;
      }

      // applyMaterial
      uint applyMaterial(
        Shader& shader, const MaterialNode& node,
        const string& prefix = "", uint tex_slot = 1
      );

      // flat_shader, frame_vertex_array
      Shader flat_shader;
      VertexArray frame_vertex_array;
    private:
      Map<string, FrameBuffer> _frame_buffers;
      HashMap<UUID, Shader> _shaders;
      HashMap<UUID, Texture> _textures;
      HashMap<UUID, VertexBuffer> _vertex_buffers;
      HashMap<UUID, IndexBuffer> _index_buffers;
      HashMap<UUID, UniformBuffer> _uniform_buffers;
      HashMap<UUID, VertexArray> _vertex_arrays;
    };
  }
}