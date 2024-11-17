#pragma once
#include "uuid.hh"

namespace Parrot {
	// Material
	class Material : public UUIDObject {
	public:
		// Material
		Material(const stdf::path& filepath);

		// shader_uuid
		uuid shader_uuid = 0;
	};
}