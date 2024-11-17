#include "common.hh"
#include "app.hh"
#include "window/window.hh"
#include "graphics/context.hh"
#include "ecs/components/render.hh"
#include "debug/debug.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
	// App
	App::App(const stdf::path& asset_dir)
		: _asset_manager(asset_dir) {}
	// addWindow
	void App::addWindow(const Window& window) {
		addWindow(Window(window));
	}
	void App::addWindow(Window&& window) {
		Window& placed = _windows.emplace(window.getUUID(), std::move(window)).first->second;
		_contexts.emplace(&placed, GPUContext([&] { placed.bind(); }, [&] { placed.unbind(); }));
	}
	// run
	void App::run() {
		LOG_CORE_INFO("app '{}' running", _name);
		if (_main_window) {
			Stopwatch frame_watch;
			while (_main_window->isOpen()) {
				seconds delta_time = frame_watch.reset();
				LOG_CORE_INFO("update app (dt = {})", delta_time);
				for (auto& [uuid, window] : _windows) {
					Scene& scene = _scenes.at(window.getSceneUUID());
					// update scene
					scene.update(delta_time);
					// draw
					GPUContext& context = _contexts.at(&window);
					// BatchRenderer::draw(context, createBatch(scene));
				}
			}
		}
		LOG_CORE_INFO("app '{}' terminated (gracefully)", _name);
	}

	}
}