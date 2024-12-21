#include "common.hh"
#include "uniform_buffer_opengl.hh"
#include "debug/debug.hh"
#include <glad/glad.hh>

namespace Parrot {
	// UniformBufferOpenGL / ~UniformBufferOpenGL
	UniformBufferOpenGL::UniformBufferOpenGL(usize size)
		: _binding_point(++s_buffer_count), _is_static(false) {
		glGenBuffers(1, &_gpu_id);
		glBindBufferBase(GL_UNIFORM_BUFFER, _binding_point, _gpu_id);
		LOG_GRAPHICS_TRACE("created uniform-buffer with id={}, binding_point={} and size={}", _gpu_id, _binding_point, size);
		bind();
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		unbind();
	}
	UniformBufferOpenGL::UniformBufferOpenGL(const void* buffer, usize size)
		: _binding_point(++s_buffer_count), _is_static(true) {
		glGenBuffers(1, &_gpu_id);
		glBindBufferBase(GL_UNIFORM_BUFFER, _binding_point, _gpu_id);
		LOG_GRAPHICS_TRACE("created uniform-buffer with id={}, binding_point={} and size={}", _gpu_id, _binding_point, size);
		bind();
		glBufferData(GL_UNIFORM_BUFFER, size, buffer, GL_STATIC_DRAW);
		unbind();
	}
	UniformBufferOpenGL::UniformBufferOpenGL(UniformBufferOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)), _binding_point(std::exchange(other._binding_point, 0)), _is_static(other._is_static) {}
	UniformBufferOpenGL::~UniformBufferOpenGL() {
		if (_gpu_id) {
			glDeleteBuffers(1, &_gpu_id);
		}
	}
	// =
	UniformBufferOpenGL& UniformBufferOpenGL::operator=(UniformBufferOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		_binding_point = std::exchange(other._binding_point, 0);
		_is_static = other._is_static;
		return *this;
	}
	// overwriteData
	void UniformBufferOpenGL::overwriteData(const void* buffer, usize size, usize offset) {
		bind();
		if (_is_static) {
			glBufferData(GL_UNIFORM_BUFFER, size, buffer, GL_STATIC_DRAW);
		}
		else {
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, buffer);
		}
		LOG_GRAPHICS_TRACE("overwrote uniform-buffer with id={} and size={}", _gpu_id, size);
		unbind();
	}
	// getBindingPoint
	uint UniformBufferOpenGL::getBindingPoint() const {
		return _binding_point;
	}
	// bind / unbind
	void UniformBufferOpenGL::bind() const {
		glBindBuffer(GL_UNIFORM_BUFFER, _gpu_id);
	}
	void UniformBufferOpenGL::unbind() {
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}