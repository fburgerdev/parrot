#pragma once
#include "utils/uuid.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  enum class DTypeGPU {
    INT32, UINT32, FLOAT32
  };
  using AttributeGPU = Pair<DTypeGPU, uint>;

  struct Vertex {
    static List<AttributeGPU> attributes();

    Vec3<float32> position = { 0, 0, 0 };
    Vec3<float32> normal = { 0, 0, -1 };
    Vec2<float32> tex_coords = { 0, 0 };
    Vec3<float32> tangent = { 1, 0, 0 };
  };

  class Mesh : public UUIDObject {
  public:
    Mesh() = default;
    template<class Vertices, class Indices>
    Mesh(Vertices&& vertices, Indices&& indices);

    void addTriangle(Vertex v1, Vertex v2, Vertex v3);
    void addQuadrangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4);

    List<Vertex> vertices;
    List<uint32> indices;
  };
}
#include "mesh_impl.hh"