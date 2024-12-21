#pragma once
#include "context_opengl.hh"
#include "block3d_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// Renderer
		class Renderer {
		public:
			// Renderer
			Renderer() = default;
			Renderer(Context& _context);

			// drawScene
			void drawScene(const SceneData& scene_data, HandleResolver resolver);
		private:
			UniformBuffer* _3d_buffer = nullptr;
			UniformBlock3D _block3d;
			Context* _context = nullptr;
		};
	}
}