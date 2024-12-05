#pragma once
#include "graphics/mesh.hh"

namespace Parrot {
	// BufferTypeOpenGL
	enum class BufferTypeOpenGL {
		STATIC, DYNAMIC
	};

	// VertexBufferOpenGL
	class VertexBufferOpenGL {
	public:
		// VertexBufferOpenGL / ~VertexBufferOpenGL
		VertexBufferOpenGL(usize size, BufferTypeOpenGL type = BufferTypeOpenGL::STATIC);
		VertexBufferOpenGL(const void* buffer, usize size, BufferTypeOpenGL type = BufferTypeOpenGL::STATIC);
		VertexBufferOpenGL(const VertexBufferOpenGL&) = delete;
		VertexBufferOpenGL(VertexBufferOpenGL&& other) noexcept;
		~VertexBufferOpenGL();
		// =
		VertexBufferOpenGL& operator=(const VertexBufferOpenGL&) = delete;
		VertexBufferOpenGL& operator=(VertexBufferOpenGL&& other) noexcept;

		// overwriteData
		void overwriteData(const void* buffer, usize size, usize offset = 0);

		// bind / unbind
		void bind() const;
		static void unbind();
	private:
		uint _gpu_id = 0;
		BufferTypeOpenGL _type;
	};

	// IndexBufferOpenGL
	class IndexBufferOpenGL {
	public:
		// IndexBufferOpenGL / ~IndexBufferOpenGL
		IndexBufferOpenGL(usize size, BufferTypeOpenGL type = BufferTypeOpenGL::STATIC);
		IndexBufferOpenGL(const uint32* indices, usize count, BufferTypeOpenGL type = BufferTypeOpenGL::STATIC);
		IndexBufferOpenGL(const IndexBufferOpenGL&) = delete;
		IndexBufferOpenGL(IndexBufferOpenGL&& other) noexcept;
		~IndexBufferOpenGL();
		// =
		IndexBufferOpenGL& operator=(const IndexBufferOpenGL&) = delete;
		IndexBufferOpenGL& operator=(IndexBufferOpenGL&& other) noexcept;

		// overwriteData
		void overwriteData(const uint32* indices, usize count, usize index = 0);

		// bind / unbind
		void bind() const;
		static void unbind();
	private:
		uint _gpu_id = 0;
		BufferTypeOpenGL _type;
	};

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