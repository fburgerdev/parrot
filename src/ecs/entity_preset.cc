#include "common.hh"
#include "entity_preset.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  EntityPreset::EntityPreset(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      json::parse(ifstream(path.file))
    );
    loadFromJSON(json, api);
  }
}