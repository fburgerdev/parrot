#include "common.hh"
#include "draw_opengl.hh"
#include "debug/debug.hh"
#include "glad/glad.hh"

namespace Parrot {
	// drawOpenGL
	void drawOpenGL(usize count) {
		LOG_GRAPHICS_TRACE("drawing {} elements...", count);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0F, 1.0F, 0.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<GLvoid*>(0));
	}
}