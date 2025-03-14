#pragma once
#include "gpu_context.hh"
#include "render_data.hh"

// OpenGL
#if defined(PARROT_OPENGL)
#include "opengl/renderer_opengl.hh"
namespace Parrot {
  // Renderer
  class Renderer : public OpenGL::Renderer {
  public:
    // (constructor)
    using OpenGL::Renderer::Renderer;
  };
}
#endif