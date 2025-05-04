#pragma once
#include "core/factory.hh"
#include "core/asset_handle.hh"
#include "core/registry.hh"
#include "core/_asset_handle.hh"
#include "component.hh"
#include "utils/math_3d.hh"

namespace Parrot {
  class EntityPreset : public Asset {
  public:
    EntityPreset(const AssetPath& asset_path, AssetAPI& api);
    EntityPreset(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    
    string tag = "Entity";
    Transform<> transform;
    List<AssetHandle<EntityPreset>> children;
    List<UniquePtr<Factory<Component>>> component_factories;
    List<string> scripts;
  };
  struct _EntityPreset {
    string tag = "Entity";
    Transform<> transform;
    List<_AssetHandle<_EntityPreset>> children;
    List<UniquePtr<Factory<Component>>> component_factories;
    List<string> scripts;
  };
}