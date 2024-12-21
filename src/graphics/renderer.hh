#pragma once
#include "gpu_context.hh"

// OpenGL
#if defined(PARROT_OPENGL)
#include "opengl/renderer_opengl.hh"
namespace Parrot {
	using Renderer = RendererOpenGL;
}
#endif