#pragma once
#include "context_opengl.hh"
#include "surface_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    class Renderer {
    public:
      Renderer() = default;
      Renderer(Context& _context);

      FrameBuffer& drawScene(
        const RenderData& render_data, const string& frame_name
      );

      FrameBuffer& mix(
        const string& target, const string& frame1, const string& frame2,
        const ShaderProgram& program
      );
      FrameBuffer& stack(
        const string& target_frame, const List<string>& frame_stack
      );

      void submit(const string& frame_name);
    private:
      List<FrameBuffer*> _frame_list;
      UniformBuffer* _3d_buffer = nullptr;
      SurfaceBlock _surface;
      Context* _context = nullptr;
    };
  }
}