#pragma once
#include "graphics/camera.hh"
#include "graphics/light_source.hh"
#include "graphics/render_object.hh"
#include "graphics/material.hh"
#include "vertex_array_opengl.hh"
#include "shader_opengl.hh"
#include "texture_opengl.hh"
#include "math/math3d.hh"

namespace Parrot {
  namespace OpenGL {
    // Context
    class Context {
    public:
      // getVertexArray
      VertexArray& getVertexArray(const Mesh& mesh);
      // getShader
      Shader& getShader(const ShaderSource& shader);
      // getTexture
      Texture& getTexture(const TextureConfig& texture);

      // createVertexBuffer
      template<class... Args>
      VertexBuffer& createVertexBuffer(Args&&... args) {
        return _vertex_buffers.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
      }
      // createIndexBuffer
      template<class... Args>
      IndexBuffer& createIndexBuffer(Args&&... args) {
        return _index_buffers.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
      }
      // createUniformBuffer
      template<class... Args>
      UniformBuffer& createUniformBuffer(Args&&... args) {
        return _uniform_buffers.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
      }
      // createVertexArray
      template<class... Args>
      VertexArray& createVertexArray(Args&&... args) {
        return _vertex_arrays.try_emplace(generateUUID(), std::forward<Args>(args)...).first->second;
      }

      // applyMaterial
      void applyMaterial(Shader& shader, const MaterialNode& node, const string& prefix = "");
    private:
      HashMap<UUID, Shader> _shaders;
      HashMap<UUID, Texture> _textures;
      HashMap<UUID, VertexBuffer> _vertex_buffers;
      HashMap<UUID, IndexBuffer> _index_buffers;
      HashMap<UUID, UniformBuffer> _uniform_buffers;
      HashMap<UUID, VertexArray> _vertex_arrays;
    };
  }
}