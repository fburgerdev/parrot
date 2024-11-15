#pragma once
#include "graphics/guard.hh"
#include "graphics/shader.hh"

namespace Parrot {
	// ShaderOpenGL
	class ShaderOpenGL {
	public:
		// ShaderOpenGL
		ShaderOpenGL(const Shader& shader, ContextGuard&& guard);
	};
}