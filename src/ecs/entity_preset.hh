#pragma once
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
    template<JsonType JSON>
    EntityPreset(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // tag
      if (json.contains("tag")) {
        tag = string(json.at("tag"));
      }
      // transform
      if (json.contains("transform")) {
        // position
        if (json.at("transform").contains("position")) {
          transform.position = Vec3<float32>(
            json.at("transform").at("position")[0],
            json.at("transform").at("position")[1],
            json.at("transform").at("position")[2]
          );
        }
        // rotation
        if (json.at("transform").contains("rotation")) {
          transform.rotation = Vec3<float32>(
            json.at("transform").at("rotation")[0],
            json.at("transform").at("rotation")[1],
            json.at("transform").at("rotation")[2]
          );
        }
        // scale
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
          children.emplace_back(child, api);
        }
      }
      // components
      if (json.contains("components")) {
        for (const auto& [name, data] : json.at("components").items()) {
          if (g_registry<
                ComponentConfig, const JSON&, const AssetPath&, AssetAPI&
              >.contains(name)) {
            components.emplace_back(
              g_registry<
                ComponentConfig, const JSON&, const AssetPath&, AssetAPI&
              >.at(name).second(data, asset_path, api)
            );
          }
          else {
            LOG_ASSET_WARNING(
              "unregistered component '{}' in json, will be ignored ", name
            );
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
    List<AssetHandle<EntityPreset>> children;
    List<UniquePtr<ComponentConfig>> components;
    List<string> scripts;
  };
}