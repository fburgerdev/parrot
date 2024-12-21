#pragma once
#include "graphics/mesh.hh"
#include "vertex_buffer_opengl.hh"
#include "index_buffer_opengl.hh"

namespace Parrot {
	// VertexArrayOpenGL
	class VertexArrayOpenGL {
	public:
		// VertexArrayOpenGL / ~VertexArrayOpenGL
		VertexArrayOpenGL(VertexBufferOpenGL&& buffer, IndexBufferOpenGL&& index, const List<AttributeGPU>& attributes);
		VertexArrayOpenGL(const VertexArrayOpenGL&) = delete;
		VertexArrayOpenGL(VertexArrayOpenGL&& other) noexcept;
		~VertexArrayOpenGL();
		// =
		VertexArrayOpenGL& operator=(const VertexArrayOpenGL&) = delete;
		VertexArrayOpenGL& operator=(VertexArrayOpenGL&& other) noexcept;

		// bind / unbind
		void bind() const;
		static void unbind();
	private:
		static uint getStride(DTypeGPU dtype, uint count);

		uint _gpu_id = 0;
		VertexBufferOpenGL _vertex;
		IndexBufferOpenGL _index;
	};
}