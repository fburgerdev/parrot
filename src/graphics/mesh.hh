#pragma once
#include "utils/uuid.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  enum class DTypeGPU {
    INT32, UINT32, FLOAT32
  };
  using AttributeGPU = Pair<DTypeGPU, uint>;

  struct Vertex {
    /// @return List of attributes
    /// so that the GPU understands the memory layout of Vertex.
    static List<AttributeGPU> attributes();

    /// @trivial
    Vec3<float32> position = { 0, 0, 0 };
    /// @warning This vector is expected to be normalized.
    Vec3<float32> normal = { 0, 0, -1 };
    /// @brief UV coordinates ranging from (0, 0) to (1, 1).
    Vec2<float32> tex_coords = { 0, 0 };
    /// @brief Tangent vector orthonormal to the @c normal.
    /// @warning This vector is expected to be normalized.
    Vec3<float32> tangent = { 1, 0, 0 };
  };

  class Mesh : public UUIDObject {
  public:
    /// @trivial
    Mesh() = default;
    template<class Vertices, class Indices>
    Mesh(Vertices&& vertices, Indices&& indices);

    void addTriangle(Vertex v1, Vertex v2, Vertex v3);
    void addQuadrangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4);

    /// @trivial
    List<Vertex> vertices;
    /// @brief List of triangle indices referring to the index in @c vertices.
    List<uint32> indices;
  };
}
#include "mesh_impl.hh"