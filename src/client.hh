#pragma once
// core
#include "core/registry.hh"
#include "core/scriptable.hh"
// app
#include "app/app.hh"
#include "app/component_registry.hh"
// ecs
#include "ecs/component.hh"
#include "ecs/entity.hh"
#include "ecs/scene.hh"
// window
#include "window/window.hh"
#include "window/window_event.hh"
// math
#include "utils/math_basic.hh"
#include "utils/math_matrix.hh"
#include "utils/math_3d.hh"
#include "utils/math_random.hh"
#include "utils/math_perlin.hh"

namespace Parrot {
  // EntityScript
  class EntityScript : public Script {
  public:
    // (constructor)
    EntityScript(Entity& entity, AssetAPI& asset_api)
      : entity(&entity), asset_api(&asset_api) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      entity->raiseEvent(e);
    }

    // entity, asset_api
    Entity* entity;
    AssetAPI* asset_api;
  private:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) {
      entity = reinterpret_cast<Entity*>(owner);
    }
  };
  // SceneScript
  class SceneScript : public Script {
  public:
    // (constructor)
    SceneScript(Scene& scene, AssetAPI& asset_api)
      : scene(&scene), asset_api(&asset_api) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      scene->raiseEvent(e);
    }

    // scene, asset_api
    Scene* scene;
    AssetAPI* asset_api;
  private:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) {
      scene = reinterpret_cast<Scene*>(owner);
    }
  };
  // StageScript
  class StageScript : public Script {
  public:
    // (constructor)
    StageScript(Stage& stage)
      : stage(&stage) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      stage->raiseEvent(e);
    }

    // Stage
    Stage* stage;
  private:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) {
      stage = reinterpret_cast<Stage*>(owner);
    }
  };
  // AppScript
  class AppScript : public Script {
  public:
    // (constructor)
    AppScript(App& app)
      : app(&app) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      app->raiseEvent(e);
    }

    // app
    App* app;
  private:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) {
      app = reinterpret_cast<App*>(owner);
    }
  };
}