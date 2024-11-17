#pragma once
#include "entity.hh"

namespace Parrot {
	// Scene
	class Scene : public UUIDObject {
	public:
		// Scene
		Scene(const stdf::path& filepath);
	private:
		string _name;
		UniquePtr<Entity> _root;
	};
}