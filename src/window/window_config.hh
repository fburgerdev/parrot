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
    WindowConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // title, width, height, cursor, /* scripts */
    string title = "Untitled Window";
    uint width = 1080, height = 720;
    CursorState cursor = CursorState::NORMAL;
    List<string> scripts;
  };
}