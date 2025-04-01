#include "common.hh"
#include "scene.hh"
#include "core/log.hh"

namespace Parrot {
  // (constructor)
  Scene::Scene(
    const SceneConfig& config, Scriptable* parent, AssetAPI& asset_api
  ) : name(config.name), root(this) {
    root = Entity(config.root.lock(), this, asset_api);
    for (const string& script : config.scripts) {
      auto [uuid, factory] = g_registry<Script, Scene&, AssetAPI&>.at(script);
      addScript(uuid, factory(*this, asset_api));
    }
  }
  // (destructor)
  Scene::~Scene() {
    Scriptable::removeAllScripts();
  }
  
  // update
  void Scene::update(float32 delta_time) {
    LOG_ECS_TRACE("update scene '{}'", name);
    root.update(delta_time);
  }

  // foreachChild (impl. Scriptable)
  void Scene::foreachChild(Func<void(Scriptable&)> func) {
    func(root);
  }
  void Scene::foreachChild(Func<void(const Scriptable&)> func) const {
    func(root);
  }
}