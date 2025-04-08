#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"

namespace Parrot {
  class StageConfig : public Asset {
  public:
    StageConfig(const AssetPath& path, AssetAPI& api);
    StageConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    AssetHandle<WindowConfig> window;
    List<AssetHandle<SceneConfig>> scenes;
    List<string> scripts;
  };
}