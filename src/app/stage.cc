#include "common.hh"
#include "stage.hh"
#include "component_registry.hh"

namespace Parrot {
  // getRenderData
  RenderData getRenderData(Scene& scene) {
    RenderData render_data;
    // camera
    auto camera_entities = scene.queryEntities<CameraComponent>();
    if (camera_entities.size() != 1) {
      LOG_ECS_ERROR(
        "scene '{}' has unexpceted count of camera-components {}, expected 1",
        scene.name, camera_entities.size()
      );
    }
    render_data.camera = {
      &camera_entities.front()->transform,
      &camera_entities.front()->getComponent<CameraComponent>()
    };
    // lights
    for (const Entity* entity : scene.queryEntities<LightComponent>()) {
      render_data.lights.emplace(
        &entity->transform,
        &entity->getComponent<LightComponent>()
      );
    }
    // render-objects
    for (const Entity* entity : scene.queryEntities<RenderObjectComponent>()) {
      auto& component = entity->getComponent<RenderObjectComponent>();
      if (component.is_opaque) {
        render_data.opaque_objects.emplace(
          &entity->transform, &component
        );
      }
      else {
        render_data.translucent_objects.emplace_back(
          &entity->transform, &component
        );
      }
    }
    return render_data;
  }

  // (constructor)
  Stage::Stage(const StageConfig& config, Scriptable* parent, AssetAPI& api)
    : Scriptable(parent),
      window(*config.window.lock(), this), _gpu_context(api) {
    for (const auto& scene : config.scenes) {
      scene_layers.emplace_back(
        Scene(*scene.lock(), this, api),
        Renderer(_gpu_context)
      );
    }
    for (const string& script_name : config.scripts) {
      auto& [id, factory] = g_registry<Script, Stage&>.at(script_name);
      addScript(id, factory(*this));
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
      if (scene.render) {
        (*scene.render)(renderer, scene);
      }
      else {
        renderer.drawScene(getRenderData(scene), "Main");
        renderer.submit("Main");
      }
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