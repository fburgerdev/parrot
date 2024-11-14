#pragma once
#include "common.hh"

namespace Parrot {
	// Shader
	class Shader {
	public:
		// Shader
		Shader(const stdf::path& filepath);

		// vertex_source, fragment_source
		string vertex_source, fragment_source;
	};
}