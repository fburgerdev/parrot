#include "common.hh"
#include "core/registry.hh"
#include "ecs/component.hh"
#include "graphics/camera.hh"
#include "graphics/light_source.hh"
#include "graphics/render_object.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  using ComponentRegistryEntry = RegistryEntry<
    ComponentConfig, const json&, const AssetPath&, AssetAPI&
  >;
  // (global) g_registry
  template<>
  Map<string, ComponentRegistryEntry> g_registry<
    ComponentConfig, const json&, const AssetPath&, AssetAPI&
  > = {
    {
      "camera",
      {
        typeid(DerivedComponentConfig<Camera>).hash_code(),
        [](const json& json, const AssetPath& asset_path, AssetAPI& asset_api) {
          return std::make_unique<DerivedComponentConfig<Camera>>(
            json, asset_path, asset_api
          );
        }
      },
    },
    {
      "light-source",
      {
        typeid(DerivedComponentConfig<LightSource>).hash_code(),
        [](const json& json, const AssetPath& asset_path, AssetAPI& asset_api) {
          return std::make_unique<DerivedComponentConfig<LightSource>>(
            json, asset_path, asset_api
          );
        }
      },
    },
    {
      "render-object",
      {
        typeid(DerivedComponentConfig<RenderObject>).hash_code(),
        [](const json& json, const AssetPath& asset_path, AssetAPI& asset_api) {
          return std::make_unique<DerivedComponentConfig<RenderObject>>(
            json, asset_path, asset_api
          );
        }
      },
    },
  };
}