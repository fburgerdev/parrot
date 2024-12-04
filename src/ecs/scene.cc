#include "common.hh"
#include "scene.hh"
#include "components/render_object.hh"
#include "debug/debug.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// Scene
	Scene::Scene(const SceneConfig& config, EntityConfigLoader loader, Scriptable* parent)
		: _name(config.name), _root(config.root ? Entity(loader(*config.root), loader, parent) : Entity(parent)) {}
	// update
	void Scene::update(float32 delta_time) {
		LOG_ECS_TRACE("update scene '{}'", _name);
		_root.update(delta_time);
	}
	// getRenderable
	List<const Entity*> Scene::getRenderable() const {
		List<const Entity*> renderable;
		Stack<const Entity*> stack({ &_root });
		while (!stack.empty()) {
			const Entity* top = stack.top();
			stack.pop();
			if (top->hasComponent<RenderObjectComponent>()) {
				renderable.push_back(top);
			}
			top->foreachChild([&](const Entity& child) {
				stack.push(&child);
			});
		}
		return renderable;
	}
}