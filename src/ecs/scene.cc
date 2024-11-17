#include "common.hh"
#include "scene.hh"
#include "components/render.hh"
#include "debug/debug.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// Scene
	Scene::Scene(const stdf::path& filepath) {
		if (filepath.string().ends_with(".json")) {
			auto data = json::parse(ifstream(filepath));
			// name
			_name = data.contains("name") ? data.at("name") : "Unnamed Scene";
		}
	}
	// update
	void Scene::update(float32 delta_time) {
		LOG_ECS_TRACE("update scene (d = {}s)", delta_time);
		if (_root) {
			_root->update(delta_time);
		}
	}
	// getRenderable
	List<const Entity*> Scene::getRenderable() const {
		if (!_root) {
			return {};
		}
		List<const Entity*> renderable;
		Stack<const Entity*> stack({ _root.get() });
		while (!stack.empty()) {
			const Entity* top = stack.top();
			stack.pop();
			if (top->hasComponent<RenderComponent>()) {
				renderable.push_back(top);
			}
			top->foreachChild([&](const Entity& child) {
				stack.push(&child);
			});
		}
		return renderable;
	}
}