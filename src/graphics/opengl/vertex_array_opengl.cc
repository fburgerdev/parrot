#include "common.hh"
#include "vertex_array_opengl.hh"
#include "debug/engine_logger.hh"
#include <glad/glad.hh>

namespace Parrot {
	namespace OpenGL {
		// VertexArray
		VertexArray::VertexArray(VertexBuffer&& vertex, IndexBuffer&& index, const List<AttributeGPU>& attributes)
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
		VertexArray::VertexArray(VertexArray&& other) noexcept
			: _gpu_id(std::exchange(other._gpu_id, 0)), _vertex(std::move(other._vertex)), _index(std::move(other._index)) {}
		// ~VertexArray
		VertexArray::~VertexArray() {
			if (_gpu_id) {
				glDeleteVertexArrays(1, &_gpu_id);
			}
		}
		// =
		VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
			_gpu_id = std::exchange(other._gpu_id, 0);
			_vertex = std::move(other._vertex);
			_index = std::move(other._index);
			return *this;
		}
		uint VertexArray::getStride(DTypeGPU dtype, uint count) {
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
		void VertexArray::bind() const {
			LOG_GRAPHICS_TRACE("bound vertex-array with id={}", _gpu_id);
			glBindVertexArray(_gpu_id);
		}
		void VertexArray::unbind() {
			LOG_GRAPHICS_TRACE("unbound vertex-array");
			glBindVertexArray(0);
		}
	}
}