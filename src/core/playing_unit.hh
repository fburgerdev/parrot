#pragma once
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/context.hh"

namespace Parrot {
	//? reconsider name
	// PlayingUnit
	class PlayingUnit : public UUIDObject, public Scriptable {
	public:
		// PlayingUnit
		PlayingUnit(Window&& window, Scene&& scene, HandleResolver resolver, Scriptable* parent = nullptr);

		// window, scene
		Window window;
		Scene scene;

		// friend
		friend class App;
	private:
		GPUContext _gpu_context;
	};
}