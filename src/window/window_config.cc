#include "common.hh"
#include "window_config.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor) for Asset
  WindowConfig::WindowConfig(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToNode(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  WindowConfig::WindowConfig(
    const SerialNode& node, const AssetPath& path, AssetAPI& api
  ) : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void WindowConfig::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    // title
    if (node.contains("title")) {
      title = string(node.at("title"));
    }
    // width, height
    if (node.contains("size")) {
      width = uint(node.at("size")[0]);
      height = uint(node.at("size")[1]);
    }
    // cursor
    if (node.contains("cursor")) {
      if (node.at("cursor") == "normal") {
        cursor = CursorState::NORMAL;
      }
      else if (node.at("cursor") == "hidden") {
        cursor = CursorState::HIDDEN;
      }
      else if (node.at("cursor") == "captured") {
        cursor = CursorState::CAPTURED;
      }
      else {
        LOG_ASSET_WARNING(
          "invalid window-config value {} for key 'cursor',"
          "defaults to 'normal'",
          node.at("cursor")
        );
      }
    }
    // scripts
    if (node.contains("scripts")) {
      for (const auto& script : node.at("scripts")) {
        scripts.emplace_back(string(script));
      }
    }
  }
}