#include "common.hh"
#include "playing_unit.hh"

namespace Parrot {
  // (constructor)
  PlayingUnit::PlayingUnit(
    const WindowConfig& window_config, const SceneConfig& scene_config,
    Scriptable* parent
  ) : window(window_config, parent), scene(scene_config, parent) {
    _renderer = Renderer(_gpu_context);
  }
  PlayingUnit::PlayingUnit(PlayingUnit&& other) noexcept
    : window(std::move(other.window)),
    scene(std::move(other.scene)),
    _gpu_context(std::move(other._gpu_context)) {
    _renderer = Renderer(_gpu_context);
  }
  // (assignment)
  PlayingUnit& PlayingUnit::operator=(PlayingUnit&& other) noexcept {
    window = std::move(other.window);
    scene = std::move(other.scene);
    _gpu_context = std::move(other._gpu_context);
    _renderer = Renderer(_gpu_context);
    return *this;
  }

  // Component
  using CameraComponent = DerivedComponent<Camera>;
  using LightSourceComponent = DerivedComponent<LightSource>;
  using RenderObjectComponent = DerivedComponent<RenderObject>;
  // draw
  void PlayingUnit::draw() {
    SceneData scene_data;
    // camera
    auto camera_entities = scene.queryEntities<CameraComponent>();
    if (camera_entities.size() != 1) {
      LOG_ECS_ERROR(
        "scene '{}' has unexpceted count of camera-components {}, expected 1",
        scene.name, camera_entities.size());
      LOG_ECS_ERROR("cancel draw");
      return;
    }
    scene_data.camera = {
      &camera_entities.front()->transform,
      &camera_entities.front()->getComponent<CameraComponent>()
    };
    // lights
    for (const Entity* entity : scene.queryEntities<LightSourceComponent>()) {
      scene_data.lights.emplace(
        &entity->transform,
        &entity->getComponent<LightSourceComponent>()
      );
    }
    // render-objects
    for (const Entity* entity : scene.queryEntities<RenderObjectComponent>()) {
      scene_data.render_objects.emplace(
        &entity->transform,
        &entity->getComponent<RenderObjectComponent>()
      );
    }
    
    _renderer.drawScene(scene_data);
  }
}