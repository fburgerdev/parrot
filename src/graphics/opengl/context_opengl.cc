#include "common.hh"
#include "context_opengl.hh"
#include "surface_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    // (static) flat_path
    static AssetPath flat_path = stdf::path(".parrot/flat.shader.json");
    
    // (constructor)
    Context::Context(AssetAPI& api)
      : flat_shader(*AssetHandle<ShaderProgram>(flat_path, api).lock()) {}

    // getFrameBuffer
    FrameBuffer& Context::getFrameBuffer(usize index) {
      return getFrameBuffer("Frame" + std::to_string(index));
    }
    FrameBuffer& Context::getFrameBuffer(const string& name) {
      if (!_frame_buffers.contains(name)) {
        // TODO: remove hard coded size
        _frame_buffers.emplace(name, FrameBuffer(1080, 720));
      }
      return _frame_buffers.at(name);
    }

    // getVertexArray
    VertexArray& Context::getVertexArray(const Mesh& mesh) {
      auto it = _vertex_arrays.find(mesh.getUUID());
      if (it == _vertex_arrays.end()) {
        return _vertex_arrays.try_emplace(
          mesh.getUUID(), 
          VertexBuffer(
            mesh.vertices.data(), mesh.vertices.size() * sizeof(Vertex)
          ),
          IndexBuffer(mesh.indices.data(), mesh.indices.size()),
          Vertex::attributes()
        ).first->second;
      }
      else {
        return it->second;
      }
    }
    // getShader
    Shader& Context::getShader(const ShaderProgram& program) {
      auto it = _shaders.find(program.getUUID());
      if (it == _shaders.end()) {
        return _shaders.emplace(
          program.getUUID(), Shader(program)
        ).first->second;
      }
      else {
        return it->second;
      }
    }
    // getTexture
    Texture& Context::getTexture(const TextureConfig& texture) {
      auto it = _textures.find(texture.getUUID());
      if (it == _textures.end()) {
        return _textures.emplace(
          texture.getUUID(), Texture(texture)
        ).first->second;
      }
      else {
        return it->second;
      }
    }

    // applyMaterial
    uint Context::applyMaterial(
      Shader& shader, const MaterialNode& node,
      const string& prefix, uint tex_slot
    ) {
      if (holds<Map<string, MaterialNode>>(node.value)) {
        const auto& object = std::get<Map<string, MaterialNode>>(node.value);
        for (const auto& [child_name, child_node] : object) {
          if (prefix.empty()) {
            tex_slot = applyMaterial(
              shader, child_node, "u_" + child_name, tex_slot
            );
          }
          else {
            tex_slot = applyMaterial(
              shader, child_node, prefix + "." + child_name, tex_slot
            );
          }
        }
      }
      else if (holds<List<MaterialNode>>(node.value)) {
        const auto& list = std::get<List<MaterialNode>>(node.value);
        for (usize i = 0; i < list.size(); ++i) {
          tex_slot = applyMaterial(
            shader, list.at(i),
            prefix + "[" + std::to_string(i) + "]", tex_slot
          );
        }
      }
      else if (holds<MaterialLeaf>(node.value)) {
        const auto& leaf = std::get<MaterialLeaf>(node.value);
        if (holds<NumericMaterialLeaf>(leaf)) {
          std::visit([&](const auto& x) {
            shader.setUniform(prefix, x);
          }, std::get<NumericMaterialLeaf>(leaf));
        }
        else if (holds<AssetHandle<TextureConfig>>(leaf)) {
          auto texture = std::get<AssetHandle<TextureConfig>>(leaf).lock();
          getTexture(*texture).bind(tex_slot);
          shader.setUniform<int32>(prefix, tex_slot);
          tex_slot += 1;
        }
        else if (holds<FrameName>(leaf)) {
          auto& frame_buffer = getFrameBuffer(std::get<FrameName>(leaf));
          frame_buffer.getTexture().bind(tex_slot);
          shader.setUniform<int32>(prefix, tex_slot);
          tex_slot += 1;
        }
      }
      return tex_slot;
    }
  }
}