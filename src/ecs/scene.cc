#include "common.hh"
#include "scene.hh"
#include "debug/debug.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// Scene / ~Scene
	Scene::Scene(const SceneConfig& config, HandleResolver resolver, Scriptable* parent)
		: _name(config.name), _root(this) {
		if (config.root) {
			resolver.useHandle<EntityConfig>([&](const EntityConfig& config) {
				_root = Entity(config, resolver, this);
			}, *config.root);
		}
	}
	Scene::~Scene() {
		Scriptable::removeAllScripts();
	}

	// foreachChild
	void Scene::foreachChild(function<void(Scriptable&)> func) {
		func(_root);
	}
	void Scene::foreachChild(function<void(const Scriptable&)> func) const {
		func(_root);
	}
	// getRoot
	Entity& Scene::getRoot() {
		return _root;
	}
	const Entity& Scene::getRoot() const {
		return _root;
	}
	// update
	void Scene::update(float32 delta_time) {
		LOG_ECS_TRACE("update scene '{}'", _name);
		_root.update(delta_time);
	}
}