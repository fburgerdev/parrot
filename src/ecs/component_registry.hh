#pragma once
#include "components/camera.hh"
#include "components/render_object.hh"

namespace Parrot {
	// ObjectFactoryFromJSON
	template<class T, class JSON >
	using ObjectFactoryFromJSON = function<UniquePtr<T>(const JSON& json)>;

	// (global) component_registry
	template<class JSON>
	inline const Map<string, ObjectFactoryFromJSON<ComponentConfig, JSON>> g_component_registry = {
		{ 
			"camera",
			[](const auto& json) {
				return std::make_unique<Camera>(json);
			}
		},
		{
			"render-object",
			[](const auto& json) {
				return std::make_unique<RenderObject>(json);
			}
		},
	};
}