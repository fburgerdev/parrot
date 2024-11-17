#pragma once
#include "uuid.hh"
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/context.hh"
#include "asset/manager.hh"
#include "graphics/batch_renderer.hh"

namespace Parrot {
	// App
	class App {
	public:
		// App
		App(const stdf::path& asset_dir);

		// addWindow
		void addWindow(const Window& window);
		void addWindow(Window&& window);
		// run
		void run();

		// createBatch
		Batch createBatch(const Scene& scene);
	private:
		string _name;
		Window* _main_window = nullptr;
		Map<uuid, Window> _windows;
		Map<uuid, Scene> _scenes;
		Map<Window*, GPUContext> _contexts;
		AssetManager _asset_manager;
	};
}