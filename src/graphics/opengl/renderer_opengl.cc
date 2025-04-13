#include "common.hh"
#include "renderer_opengl.hh"
#include "draw_opengl.hh"
#include "core/log.hh"
#include "utils/stopwatch.hh"
#include <glad/glad.hh>

namespace Parrot {
  namespace OpenGL {
    // (constructor)
    Renderer::Renderer(Context& context)
      : _context(&context) {
      _3d_buffer = &_context->createUniformBuffer(_surface.getSize());
    }
    // drawScene
    FrameBuffer& Renderer::drawScene(
      const RenderData& render_data, const string& frame_name
    ) {
      if (!_context) {
        LOG_GRAPHICS_ERROR(
          "no gpu-context specified for renderer, can't draw"
        );
        throw; // TODO: handle error
      }
      FrameBuffer& frame = _context->getFrameBuffer(frame_name);
      _frame_list.push_back(&frame);
      frame.bind();
      _surface.set(render_data);
      _3d_buffer->overwriteData(_surface.getBuffer(), _surface.getSize());
      prepareDraw();
      auto draw_render_object = [&](
        const Transform<>& transform, const RenderObject& render_object
        ) {
          auto model = render_object.model.lock();
          auto material = render_object.material.lock();
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
              shader_opengl.setUniform("u_albedo", 0);
            }
            auto proj = render_data.camera.second->calcProjectionMatrix(
              1080.0F / 720.0F
            );
            auto view = render_data.camera.first->calcGlobalViewMatrix();
            shader_opengl.setUniform(
              "u_total_time", g_global_watch.elapsed()
            );
            shader_opengl.setUniform(
              "u_local_to_world", transform.calcGlobalModelMatrix()
            );
            shader_opengl.setUniform(
              "u_local_to_world_normal", transform.calcGlobalRotationMatrix()
            );
            vertex_array.bind();
            draw(mesh.indices.size());
            vertex_array.unbind();
          }
        };
      for (auto [transform, render_object] : render_data.opaque_objects) {
        draw_render_object(*transform, *render_object);
      }
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      for (auto [transform, render_object] : render_data.translucent_objects) {
        draw_render_object(*transform, *render_object);
      }
      return frame;
    }
    
    // post-process
    // :: mix
    FrameBuffer& Renderer::mix(
      const string& target, const string& frame1, const string& frame2,
      const ShaderProgram& program
    ) {
      FrameBuffer& frame = _context->getFrameBuffer(target);
      frame.bind();
      prepareDraw();
      auto& shader = _context->getShader(program);
      shader.bind();
      shader.setUniform<int32>("u_frame1", 1);
      shader.setUniform<int32>("u_frame2", 2);
      shader.setUniform<int32>("u_frame1_depth", 3);
      shader.setUniform<int32>("u_frame2_depth", 4);
      _context->getFrameBuffer(frame1).getTexture().bind(1);
      _context->getFrameBuffer(frame2).getTexture().bind(2);
      _context->getFrameBuffer(frame1).getDepthTexture().bind(3);
      _context->getFrameBuffer(frame2).getDepthTexture().bind(4);
      _context->frame_vertex_array.bind();
      draw(6);
      return frame;
    }

    // :: stack
    FrameBuffer& Renderer::stack(
      const string& target_frame, const List<string>& frame_stack
    ) {
      FrameBuffer& frame = _context->getFrameBuffer(target_frame);
      frame.bind();
      prepareDraw();
      _context->flat_shader.bind();
      _context->flat_shader.setUniform<int32>("u_frame", 0);
      _context->frame_vertex_array.bind();
      for (const string& frame_name : frame_stack) {
        _context->getFrameBuffer(frame_name).getTexture().bind(0);
        draw(6);
      }
      return frame;
    }

    // submit
    void Renderer::submit(const string& frame_name) {
      FrameBuffer::unbind();
      prepareDraw();
      _context->flat_shader.bind();
      _context->flat_shader.setUniform<int32>("u_frame", 0);
      _context->frame_vertex_array.bind();
      _context->getFrameBuffer(frame_name).getTexture().bind(0);
      draw(6);
    }
  }
}