#pragma once
#include "core/factory.hh"
#include "core/asset_handle.hh"
#include "core/registry.hh"
#include "component.hh"
#include "utils/math_3d.hh"
#include "core/log.hh"

namespace Parrot {
  // EntityPreset (Asset)
  class EntityPreset : public Asset {
  public:
    // (constructor) for Asset
    EntityPreset(const AssetPath& asset_path, AssetAPI& api);
    EntityPreset(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    
    // tag, transform, children, components, scripts
    string tag = "Entity";
    Transform<> transform;
    List<AssetHandle<EntityPreset>> children;
    List<UniquePtr<Factory<Component>>> component_factories;
    List<string> scripts;
  };
}