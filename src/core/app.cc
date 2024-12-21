#include "common.hh"
#include "app.hh"
#include "app_config.hh"
#include "window/window.hh"
#include "graphics/render_object.hh"
#include "utils/stopwatch.hh"
#include "debug/debug.hh"

namespace Parrot {
	// DefaultEventHandler
	class DefaultEventHandler : public Script {
	public:
		// DefaultEventHandler
		DefaultEventHandler(App& app)
			: _app(&app) {}

		// resolveEvent
		virtual bool resolveEvent(const Event& e) override {
			bool success = false;
			Queue<Scriptable*> queue({ _app });
			if (const WindowEvent* we = dynamic_cast<const WindowEvent*>(&e)) {
				if (auto* wcr = we->getWindowCloseRequest()) {
					LOG_CORE_DEBUG("unresolved window-close-request, closing window '{}'...", we->getTargetWindow()->getTitle());
					we->getTargetWindow()->close();
					return true;
				}
			}
			{
				while (!queue.empty()) {
					Scriptable* front = queue.front();
					queue.pop();
					if (front->resolveEvent(e)) {
						success = true;
					}
					else {
						front->foreachChild([&](Scriptable& child) {
							queue.push(&child);
						});
					}
				}
				return success;
			}
			return false;
		}
		// setScriptOwner
		virtual void setScriptOwner(Scriptable* owner) override {
			_app = (App*)owner; //TODO: use c++ style cast
		}
		// raiseEvent
		virtual void raiseEvent(const Event& e) override {
			_app->raiseEvent(e);
		}
	private:
		App* _app;
	};
	// DefaultScriptable / ~DefaultScriptable
	DefaultScriptable::DefaultScriptable(App& app)
		: _app(app) {
		addScript<DefaultEventHandler>(app);
	}
	DefaultScriptable::~DefaultScriptable() {
		Scriptable::removeAllScripts();
	}
	// foreachChild
	void DefaultScriptable::foreachChild(function<void(Scriptable&)> func) {
		func(_app);
	}
	void DefaultScriptable::foreachChild(function<void(const Scriptable&)> func) const {
		func(_app);
	}

	// App / ~App
	App::App(const stdf::path& config_path)
		: Scriptable(&_default_scriptable), _default_scriptable(*this) {
		AppConfig config(config_path);
		LOG_CORE_INFO("creating app '{}' from {}...", config.name, config_path);
		// name
		_name = config.name;
		// asset-manager
		if (config.asset_dir.is_relative()) {
			config.asset_dir = config_path.parent_path() / config.asset_dir;
		}
		_asset_manager = AssetManager(config.asset_dir, config.loading_policy, config.unloading_policy);
		// main
		_asset_manager.getHandleResolver().useHandles(
			[&](const WindowConfig& window_config, const SceneConfig& scene_config) {
				_main_unit = &add(window_config, scene_config);
			}, config.main_window, config.main_scene
		);
		
	}
	App::~App() {
		for (auto& [id, unit] : _units) {
			unit.scene.removeAllScripts();
			unit.window.removeAllScripts();
		}
		Scriptable::removeAllScripts();
	}
	// add
	PlayingUnit& App::add(const WindowConfig& window_config, const SceneConfig& scene_config) {
		PlayingUnit unit(window_config, scene_config, _asset_manager.getHandleResolver(), this);
		unit.window.setIcon(Image("images/parrot.png")); //TODO: move
		auto result = _units.emplace(unit.getUUID(), std::move(unit));
		LOG_CORE_INFO("created playing-unit ('{}', '{}') in app '{}'", window_config.title, scene_config.name, _name);
		return result.first->second;
	}
	// getPlayingUnit
	PlayingUnit& App::getPlayingUnit(const Window& window) {
		for (auto& [uuid, unit] : _units) {
			if (&unit.window == &window) {
				return unit;
			}
		}
		throw std::runtime_error("playing-unit not found");
	}
	const PlayingUnit& App::getPlayingUnit(const Window& window) const {
		for (const auto& [uuid, unit] : _units) {
			if (&unit.window == &window) {
				return unit;
			}
		}
		throw std::runtime_error("playing-unit not found");
	}
	PlayingUnit& App::getPlayingUnit(const Scene& scene) {
		for (auto& [uuid, unit] : _units) {
			if (&unit.scene == &scene) {
				return unit;
			}
		}
		throw std::runtime_error("playing-unit not found");
	}
	const PlayingUnit& App::getPlayingUnit(const Scene& scene) const {
		for (const auto& [uuid, unit] : _units) {
			if (&unit.scene == &scene) {
				return unit;
			}
		}
		throw std::runtime_error("playing-unit not found");
	}
	// run
	void App::run() {
		if (_main_unit) {
			LOG_CORE_INFO("app '{}' running", _name);
			Stopwatch total_watch, frame_watch;
			while (_main_unit->window.isOpen()) {
				seconds delta_time = frame_watch.reset();
				LOG_CORE_TRACE("update app '{}'", _name);
				for (auto& [uuid, unit] : _units) {
					// update scene
					unit.scene.update(delta_time);
					// draw
					unit.draw(_asset_manager.getHandleResolver());
					// swap + update window
					unit.window.swapBuffers();
					for (auto& e : unit.window.pollEvents()) {
						LOG_CORE_TRACE("polled event: {}", e);
						unit.window.raiseEvent(e);
					}
				}
				//if (total_watch.elapsed() > 10) {
				//	_main_unit->window.close();
				//}
			}
			LOG_CORE_INFO("app '{}' terminated (gracefully)", _name);
		}
	}

	// foreachChild
	void App::foreachChild(function<void(Scriptable&)> func) {
		for (auto& [uuid, unit] : _units) {
			func(unit.window);
			func(unit.scene);
		}
	}
	void App::foreachChild(function<void(const Scriptable&)> func) const {
		for (const auto& [uuid, unit] : _units) {
			func(unit.window);
			func(unit.scene);
		}
	}
}