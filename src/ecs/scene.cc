#include "common.hh"
#include "scene.hh"
#include "core/log.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (constructor)
  Scene::Scene(const SceneConfig& config, Scriptable* parent)
    : name(config.name), root(this) {
    root = Entity(config.root.lock(), this);
  }
  // (destructor)
  Scene::~Scene() {
    Scriptable::removeAllScripts();
  }

  // foreachChild (scriptable)
  void Scene::foreachChild(Func<void(Scriptable&)> func) {
    func(root);
  }
  void Scene::foreachChild(Func<void(const Scriptable&)> func) const {
    func(root);
  }
  
  // update
  void Scene::update(float32 delta_time) {
    LOG_ECS_TRACE("update scene '{}'", name);
    root.update(delta_time);
  }
}