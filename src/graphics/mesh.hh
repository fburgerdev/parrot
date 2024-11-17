#pragma once
#include "uuid.hh"

namespace Parrot {
	// Mesh
	class Mesh : public UUIDObject {
	public:
		// Mesh
		Mesh(const stdf::path& filepath);
	};
}