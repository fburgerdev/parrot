#pragma once

namespace Parrot {
  template<class Vertices, class Indices>
  Mesh::Mesh(Vertices&& vertices, Indices&& indices)
    : vertices(std::forward<Vertices>(vertices)),
      indices(std::forward<Indices>(indices)) {}
}