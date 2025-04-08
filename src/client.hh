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
    EntityScript(Entity& entity, AssetAPI& asset_api);
    // raiseEvent
    virtual void raiseEvent(const Event& e) override;

    // entity, asset_api
    Entity* entity;
    AssetAPI* asset_api;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
  
  // SceneScript
  class SceneScript : public Script {
  public:
    // (constructor)
    SceneScript(Scene& scene, AssetAPI& asset_api);
    // raiseEvent
    virtual void raiseEvent(const Event& e) override;

    // scene, asset_api
    Scene* scene;
    AssetAPI* asset_api;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
  
  // StageScript
  class StageScript : public Script {
  public:
    // (constructor)
    StageScript(Stage& stage);
    // raiseEvent
    virtual void raiseEvent(const Event& e) override;

    // Stage
    Stage* stage;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };

  // AppScript
  class AppScript : public Script {
  public:
    // (constructor)
    AppScript(App& app);
    // raiseEvent
    virtual void raiseEvent(const Event& e) override;

    // app
    App* app;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
}