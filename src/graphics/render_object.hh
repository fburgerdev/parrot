#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
  // RenderObject (SubAsset)
  struct RenderObject : public Asset {
    // (constructor) for Asset
    RenderObject(const AssetPath& path, AssetAPI& api);
    template<JsonType JSON>
    RenderObject(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      model = AssetHandle<Model>(json.at("model"), api);
      if (json.contains("material")) {
        material = AssetHandle<Material>(json.at("material"), api);
      }
      else {
        material = AssetHandle<Material>(
          AssetPath(stdf::path(".parrot/model.mat.json")), api
        );
      }
      if (json.contains("opaque") && !json.at("opaque")) {
        is_opaque = false;
      }
    }

    // model, material, is_opaque
    AssetHandle<Model> model; /* PARROT_API */
    AssetHandle<Material> material; /* PARROT_API */
    bool is_opaque = true; /* PARROT_API */
  };
  // <<
  ostream& operator<<(ostream& stream, const RenderObject& render_object);
}