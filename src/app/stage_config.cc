#include "common.hh"
#include "stage_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor)
  StageConfig::StageConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = getAssetPath().applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromJSON(json, api);
  }
}