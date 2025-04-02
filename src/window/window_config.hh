#pragma once
#include "core/asset_handle.hh"
#include "core/log.hh"

namespace Parrot {
  // CursorState
  enum class CursorState {
    NORMAL, HIDDEN, CAPTURED
  };

  // WindowConfig (Asset)
  class WindowConfig : public Asset {
  public:
    // (constructor) for Asset
    WindowConfig(const AssetPath& path, AssetAPI& api);
    WindowConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
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

    // title, width, height, cursor, /* scripts */
    string title = "Untitled Window";
    uint width = 1080, height = 720;
    CursorState cursor = CursorState::NORMAL;
    List<string> scripts;
  };
}