#include "common.hh"
#include "scene_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor) for Asset
  SceneConfig::SceneConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  SceneConfig::SceneConfig(
    const SerialNode& node, const AssetPath& path, AssetAPI& api
  ) : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void SceneConfig::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    // name
    if (node.contains("name")) {
      name = string(node.at("name"));
    }
    // root
    root = AssetHandle<EntityPreset>(node.at("root"), api);
    // scripts
    if (node.contains("scripts")) {
      for (const auto& script : node.at("scripts")) {
        scripts.emplace_back(string(script));
      }
    }
  }
}