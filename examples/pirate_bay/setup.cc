#include "client.hh"
#include "scripts/fps.hh"
#include "scripts/render-main.hh"
#include "scripts/controller.hh"
#include "scripts/terrain_mesh.hh"

namespace Parrot {
  // (global) registry
  template<>
  Map<string, RegistryEntry<Script, Entity&, AssetAPI&>>
    g_registry<Script, Entity&, AssetAPI&> = {
    {
      "PlayerController",
      {
        typeid(PlayerController).hash_code(),
        [](Entity& entity, AssetAPI& asset_api) {
          return std::make_unique<PlayerController>(
            entity, asset_api
          );
        }
      }
    },
    {
      "TerrainMesh",
      {
        typeid(TerrainMesh).hash_code(),
        [](Entity& entity, AssetAPI& asset_api) {
          return std::make_unique<TerrainMesh>(
            entity, asset_api
          );
        }
      }
    },
  };
  template<>
  Map<string, RegistryEntry<Script, Scene&, AssetAPI&>>
    g_registry<Script, Scene&, AssetAPI&> = {
    {
      "RenderMain",
      {
        typeid(RenderMain).hash_code(),
        [](Scene& scene, AssetAPI& asset_api) {
          return std::make_unique<RenderMain>(scene, asset_api);
        }
      }
    },
  };
  template<>
  Map<string, RegistryEntry<Script, Window&>>
    g_registry<Script, Window&> = {};
  template<>
  Map<string, RegistryEntry<Script, Stage&>>
    g_registry<Script, Stage&> = {
    {
      "FPS",
      {
        typeid(FPS).hash_code(),
        [](Stage& stage) {
          return std::make_unique<FPS>(stage);
        }
      }
    },
  };
  template<>
  Map<string, RegistryEntry<Script, App&>>
    g_registry<Script, App&> = {};

  // setup
  stdf::path setup() {
    return stdf::path(__FILE__).parent_path() / ".app.json";
  }
}