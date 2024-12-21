#include "common.hh"
#include "renderer_opengl.hh"
#include "draw_opengl.hh"
#include "debug/debug.hh"

namespace Parrot {
	namespace OpenGL {
		// Renderer
		Renderer::Renderer(Context& context)
			: _context(&context) {
			_3d_buffer = &_context->createUniformBuffer(_block3d.getSize());
		}
		// drawScene
		void Renderer::drawScene(const SceneData& scene_data, HandleResolver resolver) {
			if (!_context) {
				LOG_GRAPHICS_ERROR("no gpu-context specified for renderer, can't draw");
				return;
			}
			_block3d.set(scene_data);
			_3d_buffer->overwriteData(_block3d.getBuffer(), _block3d.getSize());
			prepareDraw();
			for (auto [transform, render_object] : scene_data.render_objects) {
				resolver.useHandles([&](const Sidecar<Mesh>& mesh, const Material& material) {
					auto& vertex_array = _context->getVertexArray(mesh);
					resolver.useHandles([&](const ShaderSource& shader_program) {
						auto& shader_opengl = _context->getShader(shader_program);
						shader_opengl.bind();
						shader_opengl.bindUniformBuffer("u_block_3d", *_3d_buffer);
						_context->applyMaterial(shader_opengl, material.root);
						auto proj = scene_data.camera.second->calcProjectionMatrix(1080.0F / 720.0F);
						auto view = scene_data.camera.first->calcLocalViewMatrix();
						shader_opengl.setUniform("u_model", transform->calcLocalModelMatrix());
						shader_opengl.setUniform("u_model_rot", calcRotationMatrix(transform->rotation));
						vertex_array.bind();
						draw(mesh.value.indices.size());
						vertex_array.unbind();
						}, material.shader);
				}, render_object->mesh, render_object->material);
			}
		}
	}
}