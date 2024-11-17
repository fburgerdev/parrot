#pragma once
#include "graphics/shader.hh"

namespace Parrot {
	// ShaderOpenGL
	class ShaderOpenGL {
	public:
		// ShaderOpenGL
		ShaderOpenGL(const Shader& shader);
		// bind, unbind
		void bind();
		static void unbind();
	};
}