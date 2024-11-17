#pragma once
#include "graphics/mesh.hh"

namespace Parrot {
	// MeshOpenGL
	class MeshOpenGL {
	public:
		// MeshOpenGL
		MeshOpenGL(const Mesh& mesh);
		// bind, unbind
		void bind();
		static void unbind();
	};
}