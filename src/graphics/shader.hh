#pragma once
#include "uuid.hh"

namespace Parrot {
	// Shader
	class Shader : public UUIDObject {
	public:
		// Shader
		Shader(const stdf::path& filepath);

		// vertex_source, fragment_source
		string vertex_source, fragment_source;
	};
}