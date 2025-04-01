#include "common.hh"
#include "app_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor)
  AppConfig::AppConfig(const AssetPath& path)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromJSON(json);
  }
  // :: for Asset
  AppConfig::AppConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromJSON(json, api);
  }
}