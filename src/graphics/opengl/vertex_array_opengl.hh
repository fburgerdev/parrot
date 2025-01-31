#pragma once
#include "graphics/mesh.hh"
#include "vertex_buffer_opengl.hh"
#include "index_buffer_opengl.hh"

namespace Parrot {
	namespace OpenGL {
		// VertexArray
		class VertexArray {
		public:
			// (constructor)
			VertexArray(VertexBuffer&& buffer, IndexBuffer&& index, const List<AttributeGPU>& attributes);
			VertexArray(const VertexArray&) = delete;
			VertexArray(VertexArray&& other) noexcept;
      // (destructor)
			~VertexArray();
			// (assignment)
			VertexArray& operator=(const VertexArray&) = delete;
			VertexArray& operator=(VertexArray&& other) noexcept;

			// bind / unbind
			void bind() const;
			static void unbind();
		private:
			static uint getStride(DTypeGPU dtype, uint count);

			uint _gpu_id = 0;
			VertexBuffer _vertex;
			IndexBuffer _index;
		};
	}
}