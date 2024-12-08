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

		// foreachChild
		virtual void foreachChild(function<void(Scriptable&)> func) override;
		virtual void foreachChild(function<void(const Scriptable&)> func) const override;

		// friend
		friend class App;

		// window, scene
		Window window;
		Scene scene;
	private:
		GPUContext _gpu_context;
	};
}