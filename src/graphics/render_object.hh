#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
  // RenderObject (SubAsset)
  struct RenderObject : public Asset {
    // (constructor) for SubAsset
    template<JsonType JSON>
    RenderObject(
      const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json, asset_api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
      model = AssetHandle<Model>(json.at("model"), asset_api);
      if (json.contains("material")) {
        material = AssetHandle<Material>(json.at("material"), asset_api);
      }
      else {
        material = AssetHandle<Material>(
          AssetPath(stdf::path(".parrot/flat.mat.json")), asset_api
        );
      }
      if (json.contains("opaque") && !json.at("translucent")) {
        is_opaque = false;
      }
    }

    // model, material, is_opaque
    AssetHandle<Model> model;
    AssetHandle<Material> material;
    bool is_opaque = true;
  };
  // <<
  ostream& operator<<(ostream& stream, const RenderObject& render_object);
}