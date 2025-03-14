#pragma once
#include "client.hh"

namespace Parrot {
  // (global) terrain_path, reflection_terrain_path, reflect_refract_path
  inline AssetPath terrain_path = stdf::path(
    "materials/terrain.mat.json"
  );
  inline AssetPath reflection_terrain_path = stdf::path(
    "materials/reflection-terrain.mat.json"
  );
  inline AssetPath reflect_refract_path = stdf::path(
    "shaders/reflect-refract.shader.json"
  );

  // RenderMain
  class RenderMain : public SceneScript {
  public:
    // (constructor)
    using SceneScript::SceneScript;

    // onAttach
    virtual void onAttach() override {
      scene->render = [&](Renderer& renderer, Scene& scene) {
        auto render_data = getRenderData(scene);
        render_data.translucent_objects = {};

        // reflection
        for (auto* entity : scene.queryEntities<CameraComponent>()) {
          entity->transform.position.y *= -1;
          entity->transform.rotation.x *= -1;
        }
        for (auto* entity : scene.queryEntities<RenderObjectComponent>()) {
          if (entity->getTag() == "Terrain") {
            entity->getComponent<RenderObjectComponent>().material =
              AssetHandle<Material>(reflection_terrain_path, *asset_api);
          }
        }
        renderer.drawScene(render_data, "Reflection");
        for (auto* entity : scene.queryEntities<CameraComponent>()) {
          entity->transform.position.y *= -1;
          entity->transform.rotation.x *= -1;
        }
        for (auto* entity : scene.queryEntities<RenderObjectComponent>()) {
          if (entity->getTag() == "Terrain") {
            entity->getComponent<RenderObjectComponent>().material =
              AssetHandle<Material>(terrain_path, *asset_api);
          }
        }

        // normal
        renderer.drawScene(render_data, "Normal");

        // water
        render_data.opaque_objects = {};
        for (Entity* entity : scene.root.findByTag("Water")) {
          render_data.translucent_objects.emplace_back(
            &entity->transform, &entity->getComponent<RenderObjectComponent>()
          );
        }
        renderer.drawScene(render_data, "Water");

        renderer.mix(
          "Main", "Normal", "Water",
          *AssetHandle<ShaderProgram>(reflect_refract_path, *asset_api).lock()
        );
        renderer.submit("Main");
      };
    }
  };
}