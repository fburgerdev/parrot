#pragma once
#include "entity_preset.hh"

namespace Parrot {
  // SceneConfig (Asset)
  class SceneConfig : public Asset {
  public:
    // (constructor) for Asset
    SceneConfig(const AssetPath& path, AssetAPI& apit);
    SceneConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // name, root, scripts
    string name = "Unnamed Scene";
    AssetHandle<EntityPreset> root;
    List<string> scripts;
  };
}