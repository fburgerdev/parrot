#include "common.hh"
#include "stage.hh"
#include "component_registry.hh"

namespace Parrot {
  // (static) getSceneData
  static SceneData getSceneData(Scene& scene) {
    SceneData scene_data;
    // camera
    auto camera_entities = scene.queryEntities<CameraComponent>();
    if (camera_entities.size() != 1) {
      LOG_ECS_ERROR(
        "scene '{}' has unexpceted count of camera-components {}, expected 1",
        scene.name, camera_entities.size()
      );
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
      auto& component = entity->getComponent<RenderObjectComponent>();
      if (component.is_opaque) {
        scene_data.opaque_objects.emplace(
          &entity->transform, &component
        );
      }
      else {
        scene_data.translucent_objects.emplace_back(
          &entity->transform, &component
        );
      }
    }
    return scene_data;
  }

  // (constructor)
	Stage::Stage(
    const StageConfig& stage_config, Scriptable* parent, AssetAPI& asset_api
  ) : Scriptable(parent), window(*stage_config.window.lock(), this) {
    for (const auto& scene : stage_config.scenes) {
      scene_layers.emplace_back(
        Scene(*scene.lock(), this, asset_api),
        Renderer(_gpu_context)
      );
    }
	}
  // update
  void Stage::update(float32 delta_time) {
    for (auto& [scene, renderer] : scene_layers) {
      scene.update(delta_time);
    }
  }
  // render
  void Stage::render() {
    for (auto& [scene, renderer] : scene_layers) {
      renderer.drawScene(getSceneData(scene));
    }
  }

  // foreachChild
  void Stage::foreachChild(Func<void(Scriptable&)> func) {
    func(window);
    for (auto& [scene, renderer] : scene_layers) {
      func(scene);
    }

  }
  void Stage::foreachChild(Func<void(const Scriptable&)> func) const {
    func(window);
    for (const auto& [scene, renderer] : scene_layers) {
      func(scene);
    }
  }

}