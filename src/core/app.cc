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
	struct DefaultEventHandler : public Script {
		virtual bool resolveEvent(const Event& e) override {
			if (auto* wcr = e.getWindowCloseRequest()) {
				LOG_CORE_DEBUG("unresolved window-close-request, closing window '{}'...", wcr->window->getTitle());
				wcr->window->close();
				return true;
			}
			return false;
		}
	};

	// App
	App::App(const stdf::path& config_path)
		: Scriptable(&_default_scriptable), _default_scriptable(makeSingleScriptable<DefaultEventHandler>()) {
		AppConfig config(config_path);
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
	// add
	PlayingUnit& App::add(const WindowConfig& window_config, const SceneConfig& scene_config) {
		Window window(window_config);
		window.setIcon(Image("images/parrot.png")); //TODO: move
		Scene scene(scene_config, _asset_manager.getHandleResolver(), this);
		PlayingUnit unit(std::move(window), std::move(scene), _asset_manager.getHandleResolver(), this);
		auto result = _units.emplace(unit.getUUID(), std::move(unit));
		return result.first->second;
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
						raiseEvent(e);
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
}