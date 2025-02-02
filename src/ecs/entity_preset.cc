#include "common.hh"
#include "entity_preset.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  EntityPreset::EntityPreset(const AssetPath& asset_path, AssetAPI& asset_api)
    : Asset(asset_path) {
    auto json = asset_path.applySubpathToJSON(
      json::parse(ifstream(asset_path.file))
    );
    loadFromJSON(json, asset_api);
  }
}