#pragma once
#include "context.hh"

namespace Parrot {
	// Batch
	class Batch {
	public:
		// Batch
		Batch() = default;
		// add
		void add(const Mesh& mesh, const Material& material);

		// friend
		friend class BatchRenderer;
	private:
		Map<const Material*, List<const Mesh*>> _batch;
	};
	// BatchRenderer
	class BatchRenderer {
	public:
		// draw
		static void draw(GPUContext& context, const Batch& batch);
	};
}