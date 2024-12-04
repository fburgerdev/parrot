#include "common.hh"
#include "context.hh"

namespace Parrot {
	// GPUContext
	GPUContext::GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver)
		: _bind(std::move(bind)), _unbind(std::move(unbind)), _resolver(resolver) {}

	// use
	void GPUContext::use(const Mesh& mesh) {
		_bind();
		auto it = _meshes.find(mesh.getUUID());
		if (it == _meshes.end()) {
			_meshes.emplace(mesh.getUUID(), mesh).first->second.bind();
		}
		else {
			it->second.bind();
		}
	}
	void GPUContext::use(const Material& material) {
		_bind();
		_resolver.useHandles([&](const ShaderProgram& program) {
			auto it = _shaders.find(program.getUUID());
			if (it == _shaders.end()) {
				_shaders.emplace(program.getUUID(), GPUShader(program, _resolver)).first->second.bind();
			}
			else {
				it->second.bind();
			}
		}, material.shader);
		//TODO: set material values...
	}

	// draw
	void GPUContext::draw() {
		drawGPU();
	}
}