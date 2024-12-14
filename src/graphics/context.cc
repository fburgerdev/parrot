#include "common.hh"
#include "context.hh"

namespace Parrot {
	// GPUContext
	GPUContext::GPUContext(HandleResolver resolver)
		: _resolver(resolver) {}
	//GPUContext::GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver)
	//	: _bind(std::move(bind)), _unbind(std::move(unbind)), _resolver(resolver) {}

	// use
	void GPUContext::use(const Mesh& mesh, const Transform<>& transform) {
		//_bind();
		if (_current_shader) {
			_current_shader->setUniform("u_model", transform.calcModelMatrix());
			_current_shader->setUniform("u_model_rot", calcRotationMatrix(transform.rotation));
		}
		auto it = _meshes.find(mesh.getUUID());
		if (it == _meshes.end()) {
			_current_mesh = &_meshes.emplace(mesh.getUUID(), mesh).first->second;
		}
		else {
			_current_mesh = &it->second;
		}
	}
	void GPUContext::use(const Material& material, const Camera& camera, const Transform<>& camera_transform) {
		//_bind();
		auto proj = camera.calcProjectionMatrix(1080.0F / 720.0F);
		auto view = camera_transform.calcViewMatrix();
		_resolver.useHandles([&](const ShaderProgram& program) {
			auto it = _shaders.find(program.getUUID());
			if (it == _shaders.end()) {
				auto& shader = _shaders.emplace(program.getUUID(), GPUShader(program, _resolver)).first->second;
				shader.bind();
				applyMaterial(shader, material.root);
				shader.setUniform("u_proj_view", proj * view);
				_current_shader = &shader;
			}
			else {
				it->second.bind();
				it->second.setUniform("u_proj_view", proj * view);
				applyMaterial(it->second, material.root);
				_current_shader = &it->second;
			}
		}, material.shader);
	}
	// applyMaterial
	void GPUContext::applyMaterial(GPUShader& shader, const MaterialNode& node, const string& prefix) {
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
					auto it = _textures.find(texture.getUUID());
					if (it == _textures.end()) {
						auto& gpu_texture = _textures.emplace(texture.getUUID(), GPUTexture(texture, _resolver)).first->second;
						gpu_texture.bind(0);
					}
					else {
						it->second.bind(0);
					}
				}, std::get<Handle<Texture>>(leaf));
				shader.setUniform(prefix, 0);
			}
		}
	}

	// prepareDraw
	void GPUContext::prepareDraw() {
		prepareDrawGPU();
	}
	// draw
	void GPUContext::draw(usize count) {
		_current_mesh->bind();
		drawGPU(count);
		_current_mesh->unbind();
	}
}