#pragma once
#include "core/registry.hh"
#include "core/scriptable.hh"
#include "app/app.hh"
#include "app/component_registry.hh"
#include "ecs/component.hh"
#include "ecs/entity.hh"
#include "ecs/scene.hh"
#include "window/window.hh"
#include "window/window_event.hh"
#include "utils/math_basic.hh"
#include "utils/math_matrix.hh"
#include "utils/math_3d.hh"
#include "utils/math_random.hh"
#include "utils/math_perlin.hh"

namespace Parrot {
  /// @brief Script attached to Entity instances.
  class EntityScript : public Script {
  public:
    EntityScript(Entity& entity, AssetAPI& asset_api);
    virtual void raiseEvent(const Event& e) override;

    Entity* entity;
    AssetAPI* asset_api;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
  
  /// @brief Script attached to Scene instances.
  class SceneScript : public Script {
  public:
    SceneScript(Scene& scene, AssetAPI& asset_api);
    virtual void raiseEvent(const Event& e) override;

    Scene* scene;
    AssetAPI* asset_api;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
  
  /// @brief Script attached to Stage instances.
  class StageScript : public Script {
  public:
    StageScript(Stage& stage);
    virtual void raiseEvent(const Event& e) override;

    Stage* stage;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };

  /// @brief Script attached to the App instance.
  class AppScript : public Script {
  public:
    AppScript(App& app);
    virtual void raiseEvent(const Event& e) override;

    App* app;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
}