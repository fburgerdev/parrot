#include "common.hh"
#include "draw_opengl.hh"
#include "debug/engine_logger.hh"
#include <glad/glad.hh>

namespace Parrot {
  namespace OpenGL {
    // prepareDraw
    void prepareDraw() {
      LOG_GRAPHICS_TRACE("preparing opengl draw...");
      glEnable(GL_DEPTH_TEST);
      glClearColor(0.7F, 0.7F, 0.9F, 1.0F);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_CULL_FACE);
    }
    // draw
    void draw(usize count) {
      LOG_GRAPHICS_TRACE("drawing {} elements...", count);
      glDrawElements(
        GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<GLvoid*>(0)
      );
    }
  }
}