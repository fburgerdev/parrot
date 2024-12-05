#include "common.hh"
#include "context.hh"

namespace Parrot {
	// GPUContext
	GPUContext::GPUContext(HandleResolver resolver)
		: _resolver(resolver) {}
	GPUContext::GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver)
		: _bind(std::move(bind)), _unbind(std::move(unbind)), _resolver(resolver) {}

	// use
	void GPUContext::use(const Mesh& mesh, const Transform<>& transform) {
		//_bind();
		if (_current_shader) {
			_current_shader->setUniform("u_model", transform.calcModelMatrix());
			_current_shader->setUniform("u_model_rot", calcRotationMatrix(transform.rotation));
		}
		auto it = _meshes.find(mesh.getUUID());
		if (it == _meshes.end()) {
			_meshes.emplace(mesh.getUUID(), mesh).first->second.bind();
		}
		else {
			it->second.bind();
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
				shader.setUniform("u_proj_view", proj * view);
				_current_shader = &shader;
			}
			else {
				it->second.bind();
				it->second.setUniform("u_proj_view", proj * view);
				_current_shader = &it->second;
			}
		}, material.shader);
		//TODO: set material values...
	}

	// draw
	void GPUContext::draw(usize count) {
		drawGPU(count);
	}
}