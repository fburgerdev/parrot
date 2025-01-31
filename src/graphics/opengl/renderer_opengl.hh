#pragma once
#include "context_opengl.hh"
#include "surface_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// Renderer
		class Renderer {
		public:
			// (constructor)
			Renderer() = default;
			Renderer(Context& _context);

			// drawScene
			void drawScene(const SceneData& scene_data);
		private:
			UniformBuffer* _3d_buffer = nullptr;
			SurfaceBlock _surface;
			Context* _context = nullptr;
		};
	}
}