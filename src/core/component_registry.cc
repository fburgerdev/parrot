#include "common.hh"
#include "registry.hh"
#include "ecs/component.hh"
#include "graphics/camera.hh"
#include "graphics/render_object.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// (global) registry
	template<>
	Map<string, RegistryEntry<ComponentConfig, const json&, const stdf::path&>>
		g_registry<ComponentConfig, const json&, const stdf::path&> = {
		{
			"camera",
			{
				typeid(DerivedComponentConfig<Camera>).hash_code(),
				[](const json& json, const stdf::path& filepath) {
					return std::make_unique<DerivedComponentConfig<Camera>>(json, filepath);
				}
			},
		},
		{
			"render-object",
			{
				typeid(DerivedComponentConfig<RenderObject>).hash_code(),
				[](const json& json, const stdf::path& filepath) {
					return std::make_unique<DerivedComponentConfig<RenderObject>>(json, filepath);
				}
			},
		},
	};
}