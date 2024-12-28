#pragma once
#include "core/uuid.hh"
#include "math/matrix.hh"

namespace Parrot {
	// DTypeGPU
	enum class DTypeGPU {
		INT32, UINT32, FLOAT32
	};
	// AttributeGPU
	using AttributeGPU = Pair<DTypeGPU, uint>;

	// Vertex
	struct Vertex {
		// attributes
		static List<AttributeGPU> attributes() {
			return {
				{ DTypeGPU::FLOAT32, 3 },
				{ DTypeGPU::FLOAT32, 3 },
				{ DTypeGPU::FLOAT32, 2 }
			};
		}

		// position, normal, tex_coords
		Vec3<float32> position = Vec3<float32>(0, 0, 0);
		Vec3<float32> normal = Vec3<float32>(0, 0, -1);
		Vec2<float32> tex_coords = Vec2<float32>(0, 0);
	};

	// Mesh
	class Mesh : public UUIDObject {
	public:
		// Mesh
		Mesh() = default;
		Mesh(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Mesh(const JSON& json, const stdf::path& filepath) {}

		// vertices, indices
		List<Vertex> vertices;
		List<uint32> indices;
	};
}