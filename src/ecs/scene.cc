#include "common.hh"
#include "scene.hh"
#include "debug/engine_logger.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
	// Scene / ~Scene
	Scene::Scene(const SceneConfig& config, AssetHandleResolver resolver, Scriptable* parent)
		: name(config.name), root(this) {
		resolver.useHandle<EntityConfig>([&](const EntityConfig& config) {
			root = Entity(config, resolver, this);
		}, config.root);
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