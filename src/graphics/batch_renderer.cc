#include "common.hh"
#include "batch_renderer.hh"
#include "debug/debug.hh"

namespace Parrot {
	// add
	void Batch::add(const Mesh& mesh, const Material& material, const Transform<>& transform) {
		_batch[&material].emplace_back(&mesh, &transform);
	}

	// draw
	void BatchRenderer::draw(GPUContext& context, const Camera& camera, const Transform<>& camera_transform, const Batch& batch) {
		LOG_GRAPHICS_TRACE("batch renderer start");
		context.prepareDraw();
		for (const auto& [material, pairs] : batch._batch) {
			context.use(*material, camera, camera_transform);
			for (const auto [mesh, transform] : pairs) {
				context.use(*mesh, *transform);
				context.draw(mesh->indices.size());
			}
		}
		LOG_GRAPHICS_TRACE("batch renderer end");
	}
}