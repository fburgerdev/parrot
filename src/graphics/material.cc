#include "common.hh"
#include "material.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor)
  Material::Material(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
}