#pragma once
#include "context.hh"
#include "camera.hh"
#include "math/3d.hh"

namespace Parrot {
	// Batch
	class Batch {
	public:
		// Batch
		Batch() = default;
		// add
		void add(const Mesh& mesh, const Material& material, const Transform<>& transform);

		// friend
		friend class BatchRenderer;
	private:
		Map<const Material*, List<Pair<const Mesh*, const Transform<>*>>> _batch;
	};
	// BatchRenderer
	class BatchRenderer {
	public:
		// draw
		static void draw(GPUContext& context, const Camera& camera, const Transform<>& camera_transform, const Batch& batch);
	};
}