#include "common.hh"
#include "texture_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor)
  TextureConfig::TextureConfig(AssetHandle<Image> image)
    : image(std::move(image)) {}
  // :: for Asset
  TextureConfig::TextureConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromJSON(json, api);
  }
}