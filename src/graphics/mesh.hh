#pragma once
#include "uuid.hh"
#include "math/matrix.hh"

namespace Parrot {
	// Vertex
	struct Vertex {
		// position, normal, tex_coords
		Vec3<float32> position = Vec3<float32>(0, 0, 0);
		Vec3<float32> normal = Vec3<float32>(0, 0, -1);
		Vec2<float32> tex_coords = Vec2<float32>(0, 0);
	};

	// Mesh
	class Mesh : public UUIDObject {
	public:
		// Mesh
		Mesh(const stdf::path& filepath);

		// vertices, indices
		List<Vertex> vertices;
		List<uint> indices;
	};
}