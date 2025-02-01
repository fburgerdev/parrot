#include "common.hh"
#include "render_object.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
  // TODO: make << overload more verbose
  // <<
  ostream& operator<<(ostream& stream, const RenderObject& render_object) {
    return stream << "RenderObject()";
  }
}