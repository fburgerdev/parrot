#pragma once
#include "gpu_context.hh"
#include "render_data.hh"

#if defined(PARROT_OPENGL)
#include "opengl/renderer_opengl.hh"
namespace Parrot {
  class Renderer : public OpenGL::Renderer {
  public:
    using OpenGL::Renderer::Renderer;
  };
}
#endif