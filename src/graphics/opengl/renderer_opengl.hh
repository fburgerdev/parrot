#pragma once
#include "context_opengl.hh"
#include "block3d_opengl.hh"
namespace Parrot {
	// RendererOpenGL
	class RendererOpenGL {
	public:
		// RendererOpenGL
		RendererOpenGL() = default;
		RendererOpenGL(ContextOpenGL& _context);

		// drawScene
		void drawScene(const SceneData& scene_data, HandleResolver resolver);
	private:
		UniformBufferOpenGL* _3d_buffer = nullptr;
		UniformBlock3D _block3d;
		ContextOpenGL* _context = nullptr;
	};
}