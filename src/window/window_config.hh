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
    template<JsonType JSON>
    WindowConfig(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // title
      if (json.contains("title")) {
        title = string(json.at("title"));
      }
      // width, height
      if (json.contains("size")) {
        width = uint(json.at("size")[0]);
        height = uint(json.at("size")[1]);
      }
      // cursor
      if (json.contains("cursor")) {
        if (json.at("cursor") == "normal") {
          cursor = CursorState::NORMAL;
        }
        else if (json.at("cursor") == "hidden") {
          cursor = CursorState::HIDDEN;
        }
        else if (json.at("cursor") == "captured") {
          cursor = CursorState::CAPTURED;
        }
        else {
          LOG_ASSET_WARNING(
            "invalid window-config value {} for key 'cursor',"
            "defaults to 'normal'",
            json.at("cursor")
          );
        }
      }
      // scripts
      if (json.contains("scripts")) {
        for (const auto& script : json.at("scripts")) {
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