#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"

namespace Parrot {
  // StageConfig (Asset)
  class StageConfig : public Asset {
  public:
    // (constructor) for Asset
    StageConfig(const AssetPath& path, AssetAPI& api);
    StageConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // window, scenes, scripts
    AssetHandle<WindowConfig> window;
    List<AssetHandle<SceneConfig>> scenes;
    List<string> scripts;
  };
}