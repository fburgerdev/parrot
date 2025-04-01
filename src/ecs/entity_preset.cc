#include "common.hh"
#include "entity_preset.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor)
  EntityPreset::EntityPreset(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromJSON(json, api);
  }
}