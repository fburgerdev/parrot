#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
  // RenderObject (SubAsset)
  struct RenderObject : public Asset {
    // (constructor) for Asset
    RenderObject(const AssetPath& path, AssetAPI& api);
    RenderObject(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
      model = AssetHandle<Model>(node.at("model"), api);
      if (node.contains("material")) {
        material = AssetHandle<Material>(node.at("material"), api);
      }
      else {
        material = AssetHandle<Material>(
          AssetPath(stdf::path(".parrot/model.mat.json")), api
        );
      }
      if (node.contains("opaque") && !node.at("opaque")) {
        is_opaque = false;
      }
    }

    // model, material, is_opaque
    AssetHandle<Model> model; /* API */
    AssetHandle<Material> material; /* API */
    bool is_opaque = true; /* API */
  };
  // <<
  ostream& operator<<(ostream& stream, const RenderObject& render_object);
}