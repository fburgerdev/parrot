#pragma once
#include "common.hh"

namespace Parrot {
	// VertexBufferOpenGL
	class VertexBufferOpenGL {
	public:
		// VertexBufferOpenGL / ~VertexBufferOpenGL
		VertexBufferOpenGL(usize size);
		VertexBufferOpenGL(const void* buffer, usize size);
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
		bool _is_static;
	};
}