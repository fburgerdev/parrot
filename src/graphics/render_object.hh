#pragma once
#include "model.hh"
#include "material.hh"

namespace Parrot {
  struct RenderObject : public Asset {
    RenderObject(const AssetPath& path, AssetAPI& api);
    RenderObject(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    AssetHandle<Model> model;
    AssetHandle<Material> material;
    bool is_opaque = true;
  };
  ostream& operator<<(ostream& stream, const RenderObject& render_object);
}