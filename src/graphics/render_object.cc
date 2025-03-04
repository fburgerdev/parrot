#include "common.hh"
#include "render_object.hh"
#include "core/log.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor) for Asset
  RenderObject::RenderObject(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      json::parse(ifstream(path.file))
    );
    loadFromJSON(json, api);
  }

  // TODO: make << overload more verbose
  // <<
  ostream& operator<<(ostream& stream, const RenderObject& render_object) {
    return stream << "RenderObject()";
  }
}