#include "common.hh"
#include "uniform_buffer_opengl.hh"
#include "core/log.hh"
#include <glad/glad.hh>

namespace Parrot {
  namespace OpenGL {
    // (constructor)
    UniformBuffer::UniformBuffer(usize size)
      : _binding_point(++s_buffer_count), _is_static(false) {
      glGenBuffers(1, &_gpu_id);
      glBindBufferBase(GL_UNIFORM_BUFFER, _binding_point, _gpu_id);
      LOG_GRAPHICS_TRACE(
        "created uniform-buffer with id={}, binding_point={} and size={}",
        _gpu_id, _binding_point, size
      );
      bind();
      glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
      unbind();
    }
    UniformBuffer::UniformBuffer(const void* buffer, usize size)
      : _binding_point(++s_buffer_count), _is_static(true) {
      glGenBuffers(1, &_gpu_id);
      glBindBufferBase(GL_UNIFORM_BUFFER, _binding_point, _gpu_id);
      LOG_GRAPHICS_TRACE(
        "created uniform-buffer with id={}, binding_point={} and size={}",
        _gpu_id, _binding_point, size
      );
      bind();
      glBufferData(GL_UNIFORM_BUFFER, size, buffer, GL_STATIC_DRAW);
      unbind();
    }
    UniformBuffer::UniformBuffer(UniformBuffer&& other) noexcept
      : _gpu_id(std::exchange(other._gpu_id, 0)),
      _binding_point(std::exchange(other._binding_point, 0)),
      _is_static(other._is_static) {}
    // (destructor)
    UniformBuffer::~UniformBuffer() {
      if (_gpu_id) {
        glDeleteBuffers(1, &_gpu_id);
      }
    }
    // (assignment)
    UniformBuffer& UniformBuffer::operator=(UniformBuffer&& other) noexcept {
      _gpu_id = std::exchange(other._gpu_id, 0);
      _binding_point = std::exchange(other._binding_point, 0);
      _is_static = other._is_static;
      return *this;
    }
    // overwriteData
    void UniformBuffer::overwriteData(
      const void* buffer, usize size, usize offset
    ) {
      bind();
      if (_is_static) {
        glBufferData(GL_UNIFORM_BUFFER, size, buffer, GL_STATIC_DRAW);
      }
      else {
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, buffer);
      }
      LOG_GRAPHICS_TRACE(
        "overwrote uniform-buffer with id={} and size={}", _gpu_id, size
      );
      unbind();
    }
    // getBindingPoint
    uint UniformBuffer::getBindingPoint() const {
      return _binding_point;
    }
    // bind / unbind
    void UniformBuffer::bind() const {
      glBindBuffer(GL_UNIFORM_BUFFER, _gpu_id);
    }
    void UniformBuffer::unbind() {
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
  }
}