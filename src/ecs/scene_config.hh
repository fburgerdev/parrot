#pragma once
#include "entity_preset.hh"

namespace Parrot {
  // SceneConfig (Asset)
  class SceneConfig : public Asset {
  public:
    // (constructor) for Asset
    SceneConfig(const AssetPath& path, AssetAPI& apit);
    template<JsonType JSON>
    SceneConfig(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // name
      if (json.contains("name")) {
        name = string(json.at("name"));
      }
      // root
      root = AssetHandle<EntityPreset>(json.at("root"), api);
    }

    // name, root
    string name = "Unnamed Scene";
    AssetHandle<EntityPreset> root;
  };
}