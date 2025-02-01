#include "common.hh"
#include "mesh.hh"

namespace Parrot {
  // attributes
  List<AttributeGPU> Vertex::attributes() {
    return {
      { DTypeGPU::FLOAT32, 3 },
      { DTypeGPU::FLOAT32, 3 },
      { DTypeGPU::FLOAT32, 2 },
    };
  }

  // addTriangle
  void Mesh::addTriangle(Vertex v1, Vertex v2, Vertex v3) {
    usize start = vertices.size();
    vertices.emplace_back(v1);
    vertices.emplace_back(v2);
    vertices.emplace_back(v3);
    indices.push_back(start + 0);
    indices.push_back(start + 1);
    indices.push_back(start + 2);
  }
  // addQuadrangle
  void Mesh::addQuadrangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
    usize start = vertices.size();
    vertices.emplace_back(v1);
    vertices.emplace_back(v2);
    vertices.emplace_back(v3);
    vertices.emplace_back(v4);
    indices.push_back(start + 0);
    indices.push_back(start + 1);
    indices.push_back(start + 2);
    indices.push_back(start + 3);
    indices.push_back(start + 2);
    indices.push_back(start + 1);
  }
}