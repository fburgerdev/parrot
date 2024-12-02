#include "common.hh"
#include "mesh_opengl.hh"

namespace Parrot {
	// MeshOpenGL
	MeshOpenGL::MeshOpenGL(const Mesh& mesh)
		: _vertex_array(
			VertexBufferOpenGL(mesh.vertices.data(), mesh.vertices.size() * sizeof(Vertex)),
			Vertex::attributes()
		), _index_buffer(mesh.indices.data(), mesh.indices.size()) {}
	// bind, unbind
	void MeshOpenGL::bind() const {
		_vertex_array.bind();
		_index_buffer.bind(); //TODO: bind in vertex array
	}
	void MeshOpenGL::unbind() {
		VertexArrayOpenGL::unbind();
		IndexBufferOpenGL::unbind();
	}
}