#include "common.hh"
#include "scene.hh"
#include "debug/debug.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// Scene
	Scene::Scene(const SceneConfig& config, HandleResolver resolver, Scriptable* parent)
		: _name(config.name), _root(parent) {
		if (config.root) {
			resolver.useHandle<EntityConfig>([&](const EntityConfig& config) {
				_root = Entity(config, resolver, parent);
			}, *config.root);
		}
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