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
    class Context {
    public:
      Context(AssetAPI& api);

      FrameBuffer& getFrameBuffer(usize index);
      FrameBuffer& getFrameBuffer(const string& name);

      VertexArray& getVertexArray(const Mesh& mesh);
      Shader& getShader(const ShaderProgram& program);
      Texture& getTexture(const TextureConfig& texture);

      template<class... Args>
      VertexBuffer& createVertexBuffer(Args&&... args);
      template<class... Args>
      IndexBuffer& createIndexBuffer(Args&&... args);
      template<class... Args>
      UniformBuffer& createUniformBuffer(Args&&... args);
      template<class... Args>
      VertexArray& createVertexArray(Args&&... args);

      uint applyMaterial(
        Shader& shader, const MaterialNode& node,
        const string& prefix = "", uint tex_slot = 1
      );

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
#include "context_opengl_impl.hh"