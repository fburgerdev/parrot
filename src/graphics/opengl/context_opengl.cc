#include "common.hh"
#include "context_opengl.hh"

namespace Parrot {
	// ContextOpenGL
	ContextOpenGL::ContextOpenGL(HandleResolver resolver)
		: _resolver(resolver) {}

	// getMesh
	MeshOpenGL& ContextOpenGL::getMesh(const Sidecar<Mesh>& mesh) {
		auto it = _meshes.find(mesh.getUUID());
		if (it == _meshes.end()) {
			return _meshes.emplace(mesh.getUUID(), MeshOpenGL(mesh.value)).first->second;
		}
		else {
			return it->second;
		}
	}
	// getShader
	ShaderOpenGL& ContextOpenGL::getShader(const ShaderProgram& shader) {
		auto it = _shaders.find(shader.getUUID());
		if (it == _shaders.end()) {
			return _shaders.emplace(shader.getUUID(), ShaderOpenGL(shader, _resolver)).first->second;
		}
		else {
			return it->second;
		}
	}
	// getTexture
	TextureOpenGL& ContextOpenGL::getTexture(const Texture& texture) {
		auto it = _textures.find(texture.getUUID());
		if (it == _textures.end()) {
			return _textures.emplace(texture.getUUID(), TextureOpenGL(texture, _resolver)).first->second;
		}
		else {
			return it->second;
		}
	}

	// applyMaterial
	void ContextOpenGL::applyMaterial(ShaderOpenGL& shader, const MaterialNode& node, const string& prefix) {
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
			else if (std::holds_alternative<Handle<Texture>>(leaf)) {
				_resolver.useHandles([&](const Texture& texture) {
					getTexture(texture).bind(0);
				}, std::get<Handle<Texture>>(leaf));
				shader.setUniform(prefix, 0);
			}
		}
	}
}