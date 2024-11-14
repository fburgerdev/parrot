#pragma once
#include "common.hh"

namespace Parrot {
	// Material
	class Material {
	public:
		// Material
		Material(const stdf::path& filepath);

		// shader_path
		stdf::path shader_path;
	};
}