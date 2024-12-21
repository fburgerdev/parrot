#include "common.hh"
#include "index_buffer_opengl.hh"
#include "debug/debug.hh"
#include <glad/glad.hh>

namespace Parrot {
	// IndexBufferOpenGL
	IndexBufferOpenGL::IndexBufferOpenGL(usize count)
		: _is_static(false) {
		glGenBuffers(1, &_gpu_id);
		LOG_GRAPHICS_TRACE("created index-buffer with id={} and count={}", _gpu_id, count);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), nullptr, GL_DYNAMIC_DRAW);
		unbind();
	}
	IndexBufferOpenGL::IndexBufferOpenGL(const uint32* indices, usize count)
		: _is_static(true) {
		glGenBuffers(1, &_gpu_id);
		LOG_GRAPHICS_TRACE("created index-buffer with id={} and count={}", _gpu_id, count);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
		unbind();
	}
	IndexBufferOpenGL::IndexBufferOpenGL(IndexBufferOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)), _is_static(other._is_static) {}
	// ~IndexBufferOpenGL
	IndexBufferOpenGL::~IndexBufferOpenGL() {
		if (_gpu_id) {
			glDeleteBuffers(1, &_gpu_id);
		}
	}
	// =
	IndexBufferOpenGL& IndexBufferOpenGL::operator=(IndexBufferOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		_is_static = other._is_static;
		return *this;
	}
	// overwriteData
	void IndexBufferOpenGL::overwriteData(const uint32* indices, usize count, usize index) {
		bind();
		if (_is_static) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
		}
		else {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * sizeof(uint32), count * sizeof(uint32), indices);
		}
		LOG_GRAPHICS_TRACE("overwrote index-buffer with id={} and count={}", _gpu_id, count);
		unbind();
	}
	// bind / unbind
	void IndexBufferOpenGL::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _gpu_id);
		LOG_GRAPHICS_TRACE("bound index-buffer with id={}", _gpu_id);
	}
	void IndexBufferOpenGL::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		LOG_GRAPHICS_TRACE("unbound index-buffer");
	}
}