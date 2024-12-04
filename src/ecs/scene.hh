#pragma once
#include "scene_config.hh"
#include "entity.hh"

namespace Parrot {
	// Scene
	class Scene : public UUIDObject {
	public:
		// Scene
		Scene(const SceneConfig& config, EntityConfigLoader loader, Scriptable* parent = nullptr);
		// update
		void update(float32 delta_time);
		// getRenderable
		List<const Entity*> getRenderable() const;
	private:
		string _name;
		Entity _root;
	};
}