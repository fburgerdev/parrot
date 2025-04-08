#pragma once
#include "core/asset_handle.hh"
#include "core/log.hh"

namespace Parrot {
  enum class CursorState {
    NORMAL, HIDDEN, CAPTURED
  };

  class WindowConfig : public Asset {
  public:
    WindowConfig(const AssetPath& path, AssetAPI& api);
    WindowConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    string title = "Untitled Window";
    uint width = 1080, height = 720;
    CursorState cursor = CursorState::NORMAL;
    List<string> scripts;
  };
}