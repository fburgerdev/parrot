#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
  // RenderObject (SubAsset)
  struct RenderObject : public Asset {
    // (constructor) for Asset
    RenderObject(const AssetPath& path, AssetAPI& api);
    RenderObject(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // model, material, is_opaque
    AssetHandle<Model> model;
    AssetHandle<Material> material;
    bool is_opaque = true;
  };
  // << (stream)
  ostream& operator<<(ostream& stream, const RenderObject& render_object);
}