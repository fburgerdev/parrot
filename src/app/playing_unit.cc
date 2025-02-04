#include "common.hh"
#include "playing_unit.hh"

namespace Parrot {
	// PlayingUnit
	PlayingUnit::PlayingUnit(const WindowConfig& window_config, const SceneConfig& scene_config, AssetHandleResolver resolver, Scriptable* parent)
	  : window(window_config, parent), scene(scene_config, resolver, parent), _gpu_context(resolver) {
		_renderer = Renderer(_gpu_context);
	}
	PlayingUnit::PlayingUnit(PlayingUnit&& other) noexcept
		: window(std::move(other.window)),
		scene(std::move(other.scene)),
		_gpu_context(std::move(other._gpu_context)) {
		_renderer = Renderer(_gpu_context);
	}
	// =
	PlayingUnit& PlayingUnit::operator=(PlayingUnit&& other) noexcept {
		window = std::move(other.window);
		scene = std::move(other.scene);
		_gpu_context = std::move(other._gpu_context);
		_renderer = Renderer(_gpu_context);
		return *this;
	}

	// draw
	void PlayingUnit::draw(AssetHandleResolver resolver) {
		SceneData scene_data;
		// camera
		auto camera_entities = scene.queryEntities<DerivedComponent<Camera>>();
		if (camera_entities.size() != 1) {
			LOG_ECS_ERROR("scene '{}' has unexpected amount of camera-components {}, expected 1", scene.name, camera_entities.size());
			LOG_ECS_ERROR("cancel draw");
			return;
		}
		scene_data.camera = {
			&camera_entities.front()->transform,
			&camera_entities.front()->getComponent<DerivedComponent<Camera>>()
		};
		// lights
		for (const Entity* light_entity : scene.queryEntities<DerivedComponent<LightSource>>()) {
			scene_data.lights.emplace(
				&light_entity->transform,
				&light_entity->getComponent<DerivedComponent<LightSource>>()
			);
		}
		// render-objects
		for (const Entity* render_object_entity : scene.queryEntities<DerivedComponent<RenderObject>>()) {
			scene_data.render_objects.emplace(
				&render_object_entity->transform,
				&render_object_entity->getComponent<DerivedComponent<RenderObject>>()
			);
		}
		
		_renderer.drawScene(scene_data, resolver);
	}
}