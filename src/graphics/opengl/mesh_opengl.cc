#include "common.hh"
#include "mesh_opengl.hh"

namespace Parrot {
	// MeshOpenGL
	MeshOpenGL::MeshOpenGL(const Mesh& mesh)
		: _vertex_array(
			VertexBufferOpenGL(mesh.vertices.data(), mesh.vertices.size() * sizeof(Vertex)),
			IndexBufferOpenGL(mesh.indices.data(), mesh.indices.size()),
			Vertex::attributes()
		) {}
	// bind, unbind
	void MeshOpenGL::bind() const {
		_vertex_array.bind();
	}
	void MeshOpenGL::unbind() {
		VertexArrayOpenGL::unbind();
	}
}