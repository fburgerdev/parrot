#pragma once
#include "core/asset_handle.hh"
#include "core/registry.hh"
#include "component.hh"
#include "math/math3d.hh"
#include "debug/engine_logger.hh"

namespace Parrot {
  // EntityConfig (Asset)
  class EntityConfig : public Asset {
  public:
    // (constructor) for Asset
    EntityConfig() = default;
    EntityConfig(const AssetPath& asset_path, AssetAPI& asset_api);
    template<JsonType JSON>
    EntityConfig(
      const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json, asset_api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
      // tag
      if (json.contains("tag")) {
        tag = string(json.at("tag"));
      }
      // transform
      if (json.contains("transform")) {
        if (json.at("transform").contains("position")) {
          transform.position = Vec3<float32>(
            json.at("transform").at("position")[0],
            json.at("transform").at("position")[1],
            json.at("transform").at("position")[2]
          );
        }
        if (json.at("transform").contains("rotation")) {
          transform.rotation = Vec3<float32>(
            json.at("transform").at("rotation")[0],
            json.at("transform").at("rotation")[1],
            json.at("transform").at("rotation")[2]
          );
        }
        if (json.at("transform").contains("scale")) {
          transform.scale = Vec3<float32>(
            json.at("transform").at("scale")[0],
            json.at("transform").at("scale")[1],
            json.at("transform").at("scale")[2]
          );
        }
      }
      // children
      if (json.contains("children")) {
        for (const auto& child : json.at("children")) {
          children.emplace_back(child, asset_api);
        }
      }
      // components
      if (json.contains("components")) {
        for (const auto& [name, data] : json.at("components").items()) {
          if (g_registry<ComponentConfig, const JSON&, const AssetPath&, AssetAPI&>.contains(name)) {
            components.emplace_back(
              g_registry<ComponentConfig, const JSON&, const AssetPath&, AssetAPI&>.at(name).second(data, asset_path, asset_api)
            );
          }
          else {
            LOG_ASSET_WARNING("unregistered component '{}' in json, will be ignored ", name);
          }
        }
      }
      // scripts
      if (json.contains("scripts")) {
        for (const auto& script : json.at("scripts")) {
          scripts.emplace_back(string(script));
        }
      }
    }
    
    // tag, transform, children, components, scripts
    string tag = "Entity";
    Transform<> transform;
    List<AssetHandle<EntityConfig>> children;
    List<UniquePtr<ComponentConfig>> components;
    List<string> scripts;
  };
}