#include "common.hh"
#include "material.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  Material::Material(const AssetPath& asset_path, AssetAPI& asset_api)
    : Asset(asset_path) {
    auto json = asset_path.applySubpathToJSON(
      json::parse(ifstream(asset_path.file))
    );
    loadFromJSON(json, asset_api);
  }
}