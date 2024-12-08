#pragma once
#include "scene_config.hh"
#include "entity.hh"

namespace Parrot {
	// Scene
	class Scene : public UUIDObject {
	public:
		// Scene
		Scene(const SceneConfig& config, HandleResolver resolver, Scriptable* parent = nullptr);
		// update
		void update(float32 delta_time);

		// getRoot
		Entity& getRoot();
		const Entity& getRoot() const;

		// queryEntitiesByComponent
		template<class T>
		List<const Entity*> queryEntitiesByComponent() const {
			List<const Entity*> found;
			Stack<const Entity*> stack({ &_root });
			while (!stack.empty()) {
				const Entity* top = stack.top();
				stack.pop();
				if (top->hasComponent<T>()) {
					found.push_back(top);
				}
				top->foreachChild([&](const Entity& child) {
					stack.push(&child);
				});
			}
			return found;
		}
	private:
		string _name;
		Entity _root;
	};
}