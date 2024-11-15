#include "common.hh"
#include "context.hh"

namespace Parrot {
	// GPUContext
	GPUContext::GPUContext(function<void()>&& bind, function<void()>&& unbind)
		: _bind(std::move(bind)), _unbind(std::move(unbind)) {}

	// getShader
	GPUShader& GPUContext::getShader(const Shader& shader) {
		if (!_shaders.contains(&shader)) {
			_shaders.emplace(&shader, GPUShader(shader, bind()));
		}
		return _shaders.at(&shader);
	}
	// getTexture
	GPUTexture& GPUContext::getTexture(const Texture& texture) {
		if (!_textures.contains(&texture)) {
			_textures.emplace(&texture, GPUTexture(texture, bind()));
		}
		return _textures.at(&texture);
	}

	// bind
	[[nodiscard]] ContextGuard GPUContext::bind() {
		return { _bind, _unbind };
	}
}