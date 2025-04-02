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
    EntityPreset(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api) {
      // tag
      if (node.contains("tag")) {
        tag = string(node.at("tag"));
      }
      // transform
      if (node.contains("transform")) {
        // position
        if (node.at("transform").contains("position")) {
          transform.position = Vec3<float32>(
            DefaultFloat(node.at("transform").at("position")[0]),
            DefaultFloat(node.at("transform").at("position")[1]),
            DefaultFloat(node.at("transform").at("position")[2])
          );
        }
        // rotation
        if (node.at("transform").contains("rotation")) {
          transform.rotation = Vec3<float32>(
            DefaultFloat(node.at("transform").at("rotation")[0]),
            DefaultFloat(node.at("transform").at("rotation")[1]),
            DefaultFloat(node.at("transform").at("rotation")[2])
          );
        }
        // scale
        if (node.at("transform").contains("scale")) {
          transform.scale = Vec3<float32>(
            DefaultFloat(node.at("transform").at("scale")[0]),
            DefaultFloat(node.at("transform").at("scale")[1]),
            DefaultFloat(node.at("transform").at("scale")[2])
          );
        }
      }
      // children
      if (node.contains("children")) {
        for (const auto& child : node.at("children")) {
          children.emplace_back(child, api);
        }
      }
      // components
      if (node.contains("components")) {
        for (const auto& [name, data] : node.at("components").items()) {
          if (g_registry<
            Factory<Component>, const SerialNode&, const AssetPath&, AssetAPI&
              >.contains(name)) {
            component_factories.emplace_back(
              g_registry<
                Factory<Component>, const SerialNode&, const AssetPath&, AssetAPI&
              >.at(name).second(data, getAssetPath(), api)
            );
          }
          else {
            LOG_ASSET_WARNING(
              "unregistered component '{}' in node, will be ignored ", name
            );
          }
        }
      }
      // scripts
      if (node.contains("scripts")) {
        for (const auto& script : node.at("scripts")) {
          scripts.emplace_back(string(script));
        }
      }
    }
    
    // tag, transform, children, components, scripts
    string tag = "Entity";
    Transform<> transform;
    List<AssetHandle<EntityPreset>> children;
    List<UniquePtr<Factory<Component>>> component_factories;
    List<string> scripts;
  };
}