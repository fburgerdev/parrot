#include "common.hh"
#include "window_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor) for Asset
  WindowConfig::WindowConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
}