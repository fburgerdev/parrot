#include "common.hh"
#include "batch_renderer.hh"

namespace Parrot {
	// add
	void Batch::add(const Mesh& mesh, const Material& material) {
		_batch[&material].push_back(&mesh);
	}

	// draw
	void BatchRenderer::draw(GPUContext& context, const Batch& batch) {
		for (const auto& [material, meshes] : batch._batch) {
			//context.use(*material);
			for (const auto& mesh : meshes) {
				context.use(*mesh);
				context.draw();
			}
		}
	}
}