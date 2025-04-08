#include "common.hh"
#include "client.hh"

namespace Parrot {
  //* EntityScript
  // (constructor)
  EntityScript::EntityScript(Entity& entity, AssetAPI& asset_api)
    : entity(&entity), asset_api(&asset_api) {
  }
  // raiseEvent
  void EntityScript::raiseEvent(const Event& e) {
    entity->raiseEvent(e);
  }
  // setScriptOwner
  void EntityScript::setScriptOwner(Scriptable* owner) {
    entity = reinterpret_cast<Entity*>(owner);
  }

  //* SceneScript
  // (constructor)
  SceneScript::SceneScript(Scene& scene, AssetAPI& asset_api)
    : scene(&scene), asset_api(&asset_api) {
  }
  // raiseEvent
  void SceneScript::raiseEvent(const Event& e) {
    scene->raiseEvent(e);
  }
  // setScriptOwner
  void SceneScript::setScriptOwner(Scriptable* owner) {
    scene = reinterpret_cast<Scene*>(owner);
  }

  //* StageScript
  // (constructor)
  StageScript::StageScript(Stage& stage)
    : stage(&stage) {
  }
  // raiseEvent
  void StageScript::raiseEvent(const Event& e) {
    stage->raiseEvent(e);
  }
  // setScriptOwner
  void StageScript::setScriptOwner(Scriptable* owner) {
    stage = reinterpret_cast<Stage*>(owner);
  }

  //* AppScript
  // (constructor)
  AppScript::AppScript(App& app)
    : app(&app) {}
  // raiseEvent
  void AppScript::raiseEvent(const Event& e) {
    app->raiseEvent(e);
  }
  // setScriptOwner
  void AppScript::setScriptOwner(Scriptable* owner) {
    app = reinterpret_cast<App*>(owner);
  }
}