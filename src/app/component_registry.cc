#include "common.hh"
#include "component_registry.hh"
#include "core/factory.hh"
#include "core/registry.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  using ComponentRegistryEntry = RegistryEntry<
    Factory<Component>, const json&, const AssetPath&, AssetAPI&
  >;
  // (global) g_registry
  template<>
  Map<string, ComponentRegistryEntry> g_registry<
    Factory<Component>, const json&, const AssetPath&, AssetAPI&
  > = {
    {
      "camera",
      {
        typeid(BasicFactory<CameraComponent, Component>).hash_code(), [](
          const json& json, const AssetPath& asset_path, AssetAPI& asset_api
        ) {
          return std::make_unique<BasicFactory<CameraComponent, Component>>(
            json, asset_path, asset_api
          );
        }
      },
    },
    {
      "light",
      {
        typeid(BasicFactory<LightComponent, Component>).hash_code(),[](
          const json& json, const AssetPath& asset_path, AssetAPI& asset_api
        ) {
          return std::make_unique<BasicFactory<LightComponent, Component>>(
            json, asset_path, asset_api
          );
        }
      },
    },
    {
      "render-object",
      {
        typeid(BasicFactory<RenderObjectComponent, Component>).hash_code(), [](
          const json& json, const AssetPath& asset_path, AssetAPI& asset_api
        ) {
          return std::make_unique<BasicFactory<RenderObjectComponent, Component>>(
            json, asset_path, asset_api
          );
        }
      },
    },
  };
}