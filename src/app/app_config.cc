#include "common.hh"
#include "app_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  AppConfig::AppConfig(const AssetPath& asset_path, AssetAPI& asset_api)
    : Asset(asset_path) {
    auto json = asset_path.applySubpathToJSON(
      json::parse(ifstream(asset_path.filepath))
    );
    loadFromJSON(json, asset_api);
  }
}