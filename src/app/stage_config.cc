#include "common.hh"
#include "stage_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  StageConfig::StageConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = getAssetPath().applySubpathToJSON(
      json::parse(ifstream(path.file))
    );
    loadFromJSON(json, api);
  }
}