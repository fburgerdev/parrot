#include "common.hh"
#include "scene_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor)
  SceneConfig::SceneConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
}