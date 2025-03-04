#include "common.hh"
#include "material.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  Material::Material(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      json::parse(ifstream(path.file))
    );
    loadFromJSON(json, api);
  }
}