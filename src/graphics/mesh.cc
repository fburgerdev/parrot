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
}