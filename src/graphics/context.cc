#include "common.hh"
#include "context.hh"

namespace Parrot {
	// GPUContext
	GPUContext::GPUContext(function<void()>&& bind, function<void()>&& unbind, HandleResolver resolver)
		: _bind(std::move(bind)), _unbind(std::move(unbind)), _resolver(resolver) {}

	// use
	void GPUContext::use(const Mesh& mesh) {
		// TODO
	}
	void GPUContext::use(const Material& material) {
		// TODO
	}

	// draw
	void GPUContext::draw() {
		// TODO
	}
}