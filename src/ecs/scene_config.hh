#pragma once
#include "entity_preset.hh"

namespace Parrot {
  class SceneConfig : public Asset {
  public:
    SceneConfig(const AssetPath& path, AssetAPI& apit);
    SceneConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    string name = "Unnamed Scene";
    AssetHandle<EntityPreset> root;
    List<string> scripts;
  };
  struct _SceneConfig {
    string name = "Unnamed Scene";
    _AssetHandle<_EntityPreset> root;
    List<string> scripts;
  };
}