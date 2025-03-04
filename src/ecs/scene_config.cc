#include "common.hh"
#include "scene_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  SceneConfig::SceneConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      json::parse(ifstream(path.file))
    );
    loadFromJSON(json, api);
  }
}