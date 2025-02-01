#pragma once
// core
#include "core/registry.hh"
#include "core/scriptable.hh"
// app
#include "app/app.hh"
#include "app/playing_unit.hh"
// ecs
#include "ecs/component.hh"
#include "ecs/entity.hh"
#include "ecs/scene.hh"
// window
#include "window/window.hh"
#include "window/window_event.hh"
// math
#include "math/basic_math.hh"
#include "math/matrix.hh"
#include "math/math3d.hh"

namespace Parrot {
  // EntityScript
  class EntityScript : public Script {
  public:
    // (constructor)
    EntityScript(Entity& entity)
      : entity(&entity) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      entity->raiseEvent(e);
    }

    // entity
    Entity* entity;
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
    SceneScript(Scene& scene)
      : scene(&scene) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      scene->raiseEvent(e);
    }

    // scene
    Scene* scene;
  private:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) {
      scene = reinterpret_cast<Scene*>(owner);
    }
  };
  // WindowScript
  class WindowScript : public Script {
  public:
    // (constructor)
    WindowScript(Window& window)
      : window(&window) {}

    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      window->raiseEvent(e);
    }

    // Window
    Window* window;
  private:
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) {
      window = reinterpret_cast<Window*>(owner);
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