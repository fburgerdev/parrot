#include "common.hh"
#include "component_registry.hh"
#include "core/factory.hh"
#include "core/registry.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // ComponentRegistrEntry
  using ComponentRegistryEntry = RegistryEntry<
    Factory<Component>, const SerialNode&, const AssetPath&, AssetAPI&
  >;
  // factories
  using CameraFactory = BasicFactory<CameraComponent, Component>;
  using LightFactory = BasicFactory<LightComponent, Component>;
  using RenderObjectFactory = BasicFactory<RenderObjectComponent, Component>;
  // (global) g_registry
  template<>
  Map<string, ComponentRegistryEntry> g_registry<
    Factory<Component>, const SerialNode&, const AssetPath&, AssetAPI&
  > = {
    {
      "camera",
      {
        typeid(CameraFactory).hash_code(), [](
          const SerialNode& node, const AssetPath& path, AssetAPI& api
        ) {
          return std::make_unique<CameraFactory>(node, path, api);
        }
      },
    },
    {
      "light",
      {
        typeid(LightFactory).hash_code(),[](
          const SerialNode& node, const AssetPath& path, AssetAPI& api
        ) {
          return std::make_unique<LightFactory>(node, path, api);
        }
      },
    },
    {
      "render-object",
      {
        typeid(RenderObjectFactory).hash_code(), [](
          const SerialNode& node, const AssetPath& path, AssetAPI& api
        ) {
          return std::make_unique<RenderObjectFactory>(node, path, api);
        }
      },
    },
  };
}