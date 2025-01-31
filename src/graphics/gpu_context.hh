#pragma once
// OpenGL
#if defined(PARROT_OPENGL)
#include "opengl/context_opengl.hh"
namespace Parrot {
  using GPUContext = OpenGL::Context;
}
#endif