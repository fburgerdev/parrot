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

    /// @brief Reference to Entity instance the Script is attached to.
    /// @note This pointer is never null.
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

    /// @brief Reference to Scene instance the Script is attached to.
    /// @note This pointer is never null.
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

    /// @brief Reference to Stage instance the Script is attached to.
    /// @note This pointer is never null.
    Stage* stage;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };

  /// @brief Script attached to the App instance.
  class AppScript : public Script {
  public:
    AppScript(App& app);
    virtual void raiseEvent(const Event& e) override;

    /// @brief Reference to App instance the Script is attached to.
    /// @note This pointer is never null.
    App* app;
  private:
    virtual void setScriptOwner(Scriptable* owner) override;
  };
}