#include "common.hh"
#include "texture_config.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  TextureConfig::TextureConfig(AssetHandle<Image> image)
    : image(std::move(image)) {}
  // :: for Asset
  TextureConfig::TextureConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      json::parse(ifstream(path.file))
    );
    loadFromJSON(json, api);
  }
}