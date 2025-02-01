#pragma once
#include "core/uuid.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  // DTypeGPU
  enum class DTypeGPU {
    INT32, UINT32, FLOAT32
  };
  // AttributeGPU
  using AttributeGPU = Pair<DTypeGPU, uint>;

  // Vertex
  struct Vertex {
    // attributes (static)
    static List<AttributeGPU> attributes();

    // position, normal, tex_coords
    Vec3<float32> position = { 0, 0, 0 };
    Vec3<float32> normal = { 0, 0, -1 };
    Vec2<float32> tex_coords = { 0, 0 };
  };

  // Mesh
  class Mesh : public UUIDObject {
  public:
    // (constructor)
    Mesh() = default;
    template<class Vertices, class Indices>
    Mesh(Vertices&& vertices, Indices&& indices)
      : vertices(std::forward<Vertices>(vertices)),
      indices(std::forward<Indices>(indices)) {}

    // vertices, indices
    List<Vertex> vertices;
    List<uint32> indices;
  };
}