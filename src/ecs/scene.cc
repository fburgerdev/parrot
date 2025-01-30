#include "common.hh"
#include "scene.hh"
#include "debug/engine_logger.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// Scene / ~Scene
	Scene::Scene(const SceneConfig& config, Scriptable* parent)
		: name(config.name), root(this) {
		root = Entity(config.root.lock(), this);
	}
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