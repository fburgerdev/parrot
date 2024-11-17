#pragma once
#include "entity.hh"

namespace Parrot {
	// Scene
	class Scene : public UUIDObject {
	public:
		// Scene
		Scene(const stdf::path& filepath);
		// update
		void update(float32 delta_time);
		// getRenderable
		List<const Entity*> getRenderable() const;
	private:
		string _name;
		UniquePtr<Entity> _root;
	};
}