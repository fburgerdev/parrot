#pragma once
#include "common.hh"

namespace Parrot {
	// IndexBufferOpenGL
	class IndexBufferOpenGL {
	public:
		// IndexBufferOpenGL / ~IndexBufferOpenGL
		IndexBufferOpenGL(usize count);
		IndexBufferOpenGL(const uint32* indices, usize count);
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
		bool _is_static;
	};
}