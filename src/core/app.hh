#pragma once
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/context.hh"
#include "asset/manager.hh"
#include "graphics/batch_renderer.hh"

namespace Parrot {
	// App
	class App : public Scriptable {
	public:
		// App
		App(const stdf::path& config_path);

		// add
		void add(const WindowConfig& window_config, const SceneConfig& scene_config);
		// run
		void run();

		// createBatch
		Batch createBatch(const Scene& scene);
	private:
		string _name;
		Window* _main_window = nullptr;
		Map<uuid, Window> _windows;
		Map<uuid, Scene> _scenes;
		Set<Pair<uuid, uuid>> _window_scene_pairs;
		Map<Window*, GPUContext> _contexts;
		AssetManager _asset_manager;
	};
}