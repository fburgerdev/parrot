#include "common.hh"
#include "buffer_opengl.hh"
#include "glad/glad.hh"

namespace Parrot {
	// VertexBufferOpenGL
	VertexBufferOpenGL::VertexBufferOpenGL(usize size, BufferTypeOpenGL type)
		: VertexBufferOpenGL(nullptr, size, type) {}
	VertexBufferOpenGL::VertexBufferOpenGL(const void* buffer, usize size, BufferTypeOpenGL type)
		: _type(type) {
		glGenBuffers(1, &_gpu_id);
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
		if (_type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
		}
		else if (_type == BufferTypeOpenGL::DYNAMIC) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, buffer);
		}
		else {
			throw std::logic_error("unexpected branch");
		}
	}
	// bind / unbind
	void VertexBufferOpenGL::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, _gpu_id);
	}
	void VertexBufferOpenGL::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// IndexBufferOpenGL
	IndexBufferOpenGL::IndexBufferOpenGL(usize size, BufferTypeOpenGL type)
		: IndexBufferOpenGL(nullptr, size, type) {}
	IndexBufferOpenGL::IndexBufferOpenGL(const uint32* indices, usize count, BufferTypeOpenGL type)
		: _type(type) {
		glGenBuffers(1, &_gpu_id);
		bind();
		if (type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
		}
		else if (type == BufferTypeOpenGL::DYNAMIC) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_DYNAMIC_DRAW);
		}
		else {
			throw std::logic_error("unexpected branch");
		}
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
		if (_type == BufferTypeOpenGL::STATIC) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
		}
		else if (_type == BufferTypeOpenGL::DYNAMIC) {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * sizeof(uint32), count * sizeof(uint32), indices);
		}
		else {
			throw std::logic_error("unexpected branch");
		}
	}
	// bind / unbind
	void IndexBufferOpenGL::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _gpu_id);
	}
	void IndexBufferOpenGL::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// VertexArrayOpenGL
	VertexArrayOpenGL::VertexArrayOpenGL(VertexBufferOpenGL&& buffer, const List<AttributeGPU>& attributes)
		: _buffer(std::move(buffer)) {
		// generate + bind
		glGenVertexArrays(1, &_gpu_id);
		bind();
		_buffer.bind();

		// attributes
		uint32 stride = 0;
		for (const auto& [dtype, count] : attributes) {
			stride += getStride(dtype, count);
		}
		uint64 offset = 0;
		for (usize index = 0; index < attributes.size(); ++index) {
			const auto& [dtype, count] = attributes.at(index);
			glEnableVertexAttribArray(index);
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
			offset += getStride(dtype, count);
		}
	}
	VertexArrayOpenGL::VertexArrayOpenGL(VertexArrayOpenGL&& other) noexcept
		: _gpu_id(std::exchange(other._gpu_id, 0)), _buffer(std::move(other._buffer)) {}
	// ~VertexArrayOpenGL
	VertexArrayOpenGL::~VertexArrayOpenGL() {
		if (!_gpu_id) {
			glDeleteVertexArrays(1, &_gpu_id);
		}
	}
	// =
	VertexArrayOpenGL& VertexArrayOpenGL::operator=(VertexArrayOpenGL&& other) noexcept {
		_gpu_id = std::exchange(other._gpu_id, 0);
		_buffer = std::move(other._buffer);
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
		glBindVertexArray(_gpu_id);
	}
	void VertexArrayOpenGL::unbind() {
		glBindVertexArray(0);
	}
}