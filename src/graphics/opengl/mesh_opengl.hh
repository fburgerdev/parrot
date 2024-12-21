#pragma once
#include "vertex_array_opengl.hh"

namespace Parrot {
	// MeshOpenGL
	class MeshOpenGL {
	public:
		// MeshOpenGL
		MeshOpenGL(const Mesh& mesh);

		// bind, unbind
		void bind() const;
		static void unbind();
	private:
		VertexArrayOpenGL _vertex_array;
	};
}