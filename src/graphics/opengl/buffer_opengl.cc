#include "common.hh"
#include "buffer_opengl.hh"
#include "debug/debug.hh"
#include "glad/glad.hh"

namespace Parrot {
	// VertexBufferOpenGL
	VertexBufferOpenGL::VertexBufferOpenGL(usize size, BufferTypeOpenGL type)
		: VertexBufferOpenGL(nullptr, size, type) {}
	VertexBufferOpenGL::VertexBufferOpenGL(const void* buffer, usize size, BufferTypeOpenGL type)
		: _type(type) {
		glGenBuffers(1, &_gpu_id);
		LOG_GRAPHICS_TRACE("created vertex-buffer with id={} and size={}", _gpu_id, size);
		bind();
		if (type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
		}
		else if (type == BufferTypeOpenGL::DYNAMIC) {
			glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_DYNAMIC_DRAW);
		}
		else {
			throw std::logic_error("unexpected branch");
		}
		unbind();
	}
	VertexBufferOpenGL::VertexBufferOpenGL(VertexBufferOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)), _type(other._type) {}
	// ~VertexBufferOpenGL
	VertexBufferOpenGL::~VertexBufferOpenGL() {
		if (_gpu_id) {
			glDeleteBuffers(1, &_gpu_id);
		}
	}
	// =
	VertexBufferOpenGL& VertexBufferOpenGL::operator=(VertexBufferOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		_type = other._type;
		return *this;
	}
	// overwriteData
	void VertexBufferOpenGL::overwriteData(const void* buffer, usize size, usize offset) {
		bind();
		if (_type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
		}
		else if (_type == BufferTypeOpenGL::DYNAMIC) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, buffer);
		}
		else {
			throw std::logic_error("unexpected branch");
		}
		LOG_GRAPHICS_TRACE("overwrote vertex-buffer with id={} and size={}", _gpu_id, size);
		unbind();
	}
	// bind / unbind
	void VertexBufferOpenGL::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, _gpu_id);
		LOG_GRAPHICS_TRACE("bound vertex-buffer with id={}", _gpu_id);
	}
	void VertexBufferOpenGL::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		LOG_GRAPHICS_TRACE("unbound vertex-buffer");
	}

	// IndexBufferOpenGL
	IndexBufferOpenGL::IndexBufferOpenGL(usize size, BufferTypeOpenGL type)
		: IndexBufferOpenGL(nullptr, size, type) {}
	IndexBufferOpenGL::IndexBufferOpenGL(const uint32* indices, usize count, BufferTypeOpenGL type)
		: _type(type) {
		glGenBuffers(1, &_gpu_id);
		LOG_GRAPHICS_TRACE("created index-buffer with id={} and count={}", _gpu_id, count);
		bind();
		if (type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
		}
		else if (type == BufferTypeOpenGL::DYNAMIC) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_DYNAMIC_DRAW);
		}
		else {
			throw std::logic_error("unexpected branch");
		}
		unbind();
	}
	IndexBufferOpenGL::IndexBufferOpenGL(IndexBufferOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)), _type(other._type) {}
	// ~IndexBufferOpenGL
	IndexBufferOpenGL::~IndexBufferOpenGL() {
		if (_gpu_id) {
			glDeleteBuffers(1, &_gpu_id);
		}
	}
	// =
	IndexBufferOpenGL& IndexBufferOpenGL::operator=(IndexBufferOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		_type = other._type;
		return *this;
	}
	// overwriteData
	void IndexBufferOpenGL::overwriteData(const uint32* indices, usize count, usize index) {
		bind();
		if (_type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
		}
		else if (_type == BufferTypeOpenGL::DYNAMIC) {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * sizeof(uint32), count * sizeof(uint32), indices);
		}
		else {
			throw std::logic_error("unexpected branch");
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

	// VertexArrayOpenGL
	VertexArrayOpenGL::VertexArrayOpenGL(VertexBufferOpenGL&& vertex, IndexBufferOpenGL&& index, const List<AttributeGPU>& attributes)
		: _vertex(std::move(vertex)), _index(std::move(index)) {
		// generate + bind
		glGenVertexArrays(1, &_gpu_id);
		LOG_GRAPHICS_TRACE("created vertex-array with id={}", _gpu_id);
		bind();
		_vertex.bind();
		_index.bind();

		// attributes
		uint32 stride = 0;
		for (const auto& [dtype, count] : attributes) {
			stride += getStride(dtype, count);
		}
		uint64 offset = 0;
		for (usize index = 0; index < attributes.size(); ++index) {
			const auto& [dtype, count] = attributes.at(index);
			switch (dtype) {
			case DTypeGPU::INT32:
				glVertexAttribIPointer(index, count, GL_INT, stride, (const void*)offset);
				break;
			case DTypeGPU::UINT32:
				glVertexAttribIPointer(index, count, GL_UNSIGNED_INT, stride, (const void*)offset);
				break;
			case DTypeGPU::FLOAT32:
				glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
				break;
			default:
				throw std::logic_error("unexpected branch");
			}
			glEnableVertexAttribArray(index);
			offset += getStride(dtype, count);
		}
		unbind();
		_vertex.unbind();
		_index.unbind();
	}
	VertexArrayOpenGL::VertexArrayOpenGL(VertexArrayOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)), _vertex(std::move(other._vertex)), _index(std::move(other._index)) {}
	// ~VertexArrayOpenGL
	VertexArrayOpenGL::~VertexArrayOpenGL() {
		if (_gpu_id) {
			glDeleteVertexArrays(1, &_gpu_id);
		}
	}
	// =
	VertexArrayOpenGL& VertexArrayOpenGL::operator=(VertexArrayOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		_vertex = std::move(other._vertex);
		_index = std::move(other._index);
		return *this;
	}
	uint VertexArrayOpenGL::getStride(DTypeGPU dtype, uint count) {
		switch (dtype) {
		case DTypeGPU::INT32:
			return sizeof(int32) * count;
		case DTypeGPU::UINT32:
			return sizeof(uint32) * count;
		case DTypeGPU::FLOAT32:
			return sizeof(float32) * count;
		default:
			throw std::logic_error("unexpected branch");
		}
	}
	// bind / unbind
	void VertexArrayOpenGL::bind() const {
		LOG_GRAPHICS_TRACE("bound vertex-array with id={}", _gpu_id);
		glBindVertexArray(_gpu_id);
	}
	void VertexArrayOpenGL::unbind() {
		LOG_GRAPHICS_TRACE("unbound vertex-array");
		glBindVertexArray(0);
	}
}