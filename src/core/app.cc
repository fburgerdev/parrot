#include "common.hh"
#include "app.hh"
#include "app_config.hh"
#include "window/window.hh"
#include "graphics/context.hh"
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
			if (auto* wcr = e.getWindowCloseRequest()) {
				LOG_CORE_DEBUG("unresolved window-close-request, closing window '{}'...", wcr->window->getTitle());
				wcr->window->close();
				return true;
			}
			else if (auto* window = e.getTargetWindow()){
				bool success = false;
				PlayingUnit& unit = _app->getPlayingUnit(*window);
				Queue<Scriptable*> queue({ &unit.window, &unit.scene });
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
					draw(unit);
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

	// draw
	void App::draw(PlayingUnit& unit) {
		Batch batch;
		/*
			note that we need to store the AssetViews,
			so that the AssetManager garantuees that the resources are not freed
		*/
		List<AssetView<Mesh>> mesh_views;
		List<AssetView<Material>> material_views;
		for (const Entity* entity : unit.scene.queryEntitiesByComponent<DerivedComponent<RenderObject>>()) {
			const auto& roc = entity->getComponent<DerivedComponent<RenderObject>>();
			auto mesh_view = _asset_manager.asset<Mesh>(roc.mesh_uuid);
			mesh_views.push_back(mesh_view);
			auto material_view = _asset_manager.asset<Material>(roc.material_uuid);
			material_views.push_back(material_view);
			batch.add(*mesh_view, *material_view, entity->transform);
		}
		List<const Entity*> cameras = unit.scene.queryEntitiesByComponent<DerivedComponent<Camera>>();
		unit.window.bind();
		BatchRenderer::draw(
			unit._gpu_context,
			cameras.front()->getComponent<DerivedComponent<Camera>>(),
			cameras.front()->transform,
			batch
		);
		unit.window.unbind();
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