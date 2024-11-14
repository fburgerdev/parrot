#pragma once
#include "common.hh"

namespace Parrot {
	// Scene
	class Scene {
	public:
		// Scene
		Scene(const stdf::path& filepath);
	private:
		string _name;
	};
}