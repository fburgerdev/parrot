#include "common.hh"
#include "draw_opengl.hh"
#include "debug/debug.hh"
#include <glad/glad.hh>

namespace Parrot {
	// drawOpenGL
	void drawOpenGL(usize count) {
		LOG_GRAPHICS_TRACE("drawing {} elements...", count);

		//TODO: move this to a dedicated prepare function
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.7F, 0.7F, 0.9F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<GLvoid*>(0));
	}
}