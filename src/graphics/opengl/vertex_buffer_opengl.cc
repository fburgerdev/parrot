#include "common.hh"
#include "vertex_buffer_opengl.hh"
#include "debug/engine_logger.hh"
#include <glad/glad.hh>

namespace Parrot {
  namespace OpenGL {
    // (constructor)
    VertexBuffer::VertexBuffer(usize size)
      : _is_static(false) {
      glGenBuffers(1, &_gpu_id);
      LOG_GRAPHICS_TRACE("created vertex-buffer with id={} and size={}", _gpu_id, size);
      bind();
      glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
      unbind();
    }
    VertexBuffer::VertexBuffer(const void* buffer, usize size)
      : _is_static(true) {
      glGenBuffers(1, &_gpu_id);
      LOG_GRAPHICS_TRACE("created vertex-buffer with id={} and size={}", _gpu_id, size);
      bind();
      glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
      unbind();
    }
    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
      : _gpu_id(std::exchange(other._gpu_id, 0)), _is_static(other._is_static) {}
    // (destructor)
    VertexBuffer::~VertexBuffer() {
      if (_gpu_id) {
        glDeleteBuffers(1, &_gpu_id);
      }
    }
    // (assignment)
    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
      _gpu_id = std::exchange(other._gpu_id, 0);
      _is_static = other._is_static;
      return *this;
    }
    // overwriteData
    void VertexBuffer::overwriteData(const void* buffer, usize size, usize offset) {
      bind();
      if (_is_static) {
        glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
      }
      else {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, buffer);
      }
      LOG_GRAPHICS_TRACE("overwrote vertex-buffer with id={} and size={}", _gpu_id, size);
      unbind();
    }
    // bind / unbind
    void VertexBuffer::bind() const {
      glBindBuffer(GL_ARRAY_BUFFER, _gpu_id);
      LOG_GRAPHICS_TRACE("bound vertex-buffer with id={}", _gpu_id);
    }
    void VertexBuffer::unbind() {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      LOG_GRAPHICS_TRACE("unbound vertex-buffer");
    }
  }
}