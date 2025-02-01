#include "common.hh"
#include "renderer_opengl.hh"
#include "draw_opengl.hh"
#include "core/log.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
  namespace OpenGL {
    // (constructor)
    Renderer::Renderer(Context& context)
      : _context(&context) {
      _3d_buffer = &_context->createUniformBuffer(_surface.getSize());
    }
    // drawScene
    void Renderer::drawScene(const SceneData& scene_data) {
      if (!_context) {
        LOG_GRAPHICS_ERROR(
          "no gpu-context specified for renderer, can't draw"
        );
        return;
      }
      _surface.set(scene_data);
      _3d_buffer->overwriteData(_surface.getBuffer(), _surface.getSize());
      prepareDraw();
      for (auto [transform, render_object] : scene_data.render_objects) {
        auto model = render_object->model.lock();
        auto material = render_object->material.lock();
        auto shader = material->shader.lock();
        for (const auto& [mesh, material_index] : model->submodels) {
          auto& vertex_array = _context->getVertexArray(mesh);
          auto& shader_opengl = _context->getShader(*shader);
          shader_opengl.bind();
          shader_opengl.bindUniformBuffer("u_std", *_3d_buffer);
          _context->applyMaterial(shader_opengl, material->root);
          auto& model_material = model->model_materials.at(material_index);
          if (model_material.tex_index != 0xFFFFFF) {
            _context->getTexture(
              model->textures.at(model_material.tex_index)
            ).bind(0);
          }
          auto proj = scene_data.camera.second->calcProjectionMatrix(
            1080.0F / 720.0F
          );
          auto view = scene_data.camera.first->calcLocalViewMatrix();
          shader_opengl.setUniform(
            "u_total_time", g_global_watch.elapsed()
          );
          shader_opengl.setUniform(
            "u_local_to_world", transform->calcLocalModelMatrix()
          );
          shader_opengl.setUniform(
            "u_local_to_world_normal", calcRotationMatrix(transform->rotation)
          );
          vertex_array.bind();
          draw(mesh.indices.size());
          vertex_array.unbind();
        }
      }
    }
  }
}