#include "common.hh"
#include "context_opengl.hh"
#include "surface_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// Context
		Context::Context(HandleResolver resolver)
			: _resolver(resolver) {}

		// getVertexArray
		VertexArray& Context::getVertexArray(const Sidecar<Mesh>& mesh) {
			auto it = _vertex_arrays.find(mesh.getUUID());
			if (it == _vertex_arrays.end()) {
				return _vertex_arrays.try_emplace(mesh.getUUID(), 
					VertexBuffer(mesh.value.vertices.data(), mesh.value.vertices.size() * sizeof(Vertex)),
					IndexBuffer(mesh.value.indices.data(), mesh.value.indices.size()),
					Vertex::attributes()
				).first->second;
			}
			else {
				return it->second;
			}
		}
		// getShader
		Shader& Context::getShader(const Sidecar<ShaderBuilder>& shader) {
			auto it = _shaders.find(shader.getUUID());
			if (it == _shaders.end()) {
				ShaderBuilder builder = shader.value;
				List<ShaderBuilder> snippets = { g_surface_snippet };
				builder.resolve(snippets);
				return _shaders.emplace(shader.getUUID(), Shader(builder)).first->second;
			}
			else {
				return it->second;
			}
		}
		// getTexture
		Texture& Context::getTexture(const TextureConfig& texture) {
			auto it = _textures.find(texture.getUUID());
			if (it == _textures.end()) {
				return _textures.emplace(texture.getUUID(), Texture(texture, _resolver)).first->second;
			}
			else {
				return it->second;
			}
		}

		// applyMaterial
		void Context::applyMaterial(Shader& shader, const MaterialNode& node, const string& prefix) {
			if (std::holds_alternative<Map<string, MaterialNode>>(node.value)) {
				const auto& object = std::get<Map<string, MaterialNode>>(node.value);
				for (const auto& [child_name, child_node] : object) {
					if (prefix.empty()) {
						applyMaterial(shader, child_node, "u_" + child_name);
					}
					else {
						applyMaterial(shader, child_node, prefix + "." + child_name);
					}
				}
			}
			else if (std::holds_alternative<List<MaterialNode>>(node.value)) {
				const auto& list = std::get<List<MaterialNode>>(node.value);
				for (usize i = 0; i < list.size(); ++i) {
					applyMaterial(shader, list.at(i), prefix + "[" + std::to_string(i) + "]");
				}
			}
			else if (std::holds_alternative<MaterialLeaf>(node.value)) {
				const auto& leaf = std::get<MaterialLeaf>(node.value);
				if (std::holds_alternative<NumericMaterialLeaf>(leaf)) {
					std::visit([&](const auto& x) {
						shader.setUniform(prefix, x);
						}, std::get<NumericMaterialLeaf>(leaf));
				}
				else if (std::holds_alternative<Handle<TextureConfig>>(leaf)) {
					_resolver.useHandles([&](const TextureConfig& texture) {
						getTexture(texture).bind(0);
						}, std::get<Handle<TextureConfig>>(leaf));
					shader.setUniform(prefix, 0);
				}
			}
		}
	}
}