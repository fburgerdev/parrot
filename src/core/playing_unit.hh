#pragma once
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/context.hh"

namespace Parrot {
	//TODO: reconsider name
	// PlayingUnit
	class PlayingUnit : public UUIDObject, public Scriptable {
	public:
		// PlayingUnit
		PlayingUnit(Window&& window, Scene&& scene, Scriptable* parent = nullptr);

		// window, scene
		Window window;
		Scene scene;
	private:
		GPUContext _gpu_context;
	};
}