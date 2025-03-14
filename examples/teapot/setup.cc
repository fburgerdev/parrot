#include "client.hh"
#include "scripts/rotate.hh"

namespace Parrot {
  // (global) registry
  template<>
  Map<string, RegistryEntry<Script, Entity&, AssetAPI&>>
    g_registry<Script, Entity&, AssetAPI&> = {
    {
      "Rotate",
      {
        typeid(Rotate).hash_code(),
        [](Entity& entity, AssetAPI& asset_api) {
          return std::make_unique<Rotate>(
            entity, asset_api
          );
        }
      }
    },
  };
  template<>
  Map<string, RegistryEntry<Script, Scene&, AssetAPI&>>
    g_registry<Script, Scene&, AssetAPI&> = {};
  template<>
  Map<string, RegistryEntry<Script, Window&>>
    g_registry<Script, Window&> = {};
  template<>
  Map<string, RegistryEntry<Script, Stage&>>
    g_registry<Script, Stage&> = {};
  template<>
  Map<string, RegistryEntry<Script, App&>>
    g_registry<Script, App&> = {};

  // setup
  stdf::path setup() {
    return stdf::path(__FILE__).parent_path() / ".app.json";
  }
}