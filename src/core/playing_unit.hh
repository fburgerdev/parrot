#pragma once
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/context.hh"

namespace Parrot {
	//? reconsider name
	// PlayingUnit
	class PlayingUnit : public UUIDObject {
	public:
		// PlayingUnit
		PlayingUnit(const WindowConfig& window_config, const SceneConfig& scene_config, HandleResolver resolver, Scriptable* parent = nullptr);

		// friend
		friend class App;

		// window, scene
		Window window;
		Scene scene;
	private:
		GPUContext _gpu_context;
	};
}