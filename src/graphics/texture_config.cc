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
    loadFromSerialNode(json, api);
  }
  TextureConfig::TextureConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void TextureConfig::loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
    image = AssetHandle<Image>(node.at("image"), api);
    //TODO: properties...
  }
}