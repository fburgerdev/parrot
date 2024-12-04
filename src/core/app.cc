#include "common.hh"
#include "app.hh"
#include "app_config.hh"
#include "window/window.hh"
#include "graphics/context.hh"
#include "ecs/components/render_object.hh"
#include "debug/debug.hh"
#include "utils/stopwatch.hh"

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
		_asset_manager.useHandles(
			[&](const WindowConfig& window_config, const SceneConfig& scene_config) {
				_main_unit = &add(window_config, scene_config);
			}, config.main_window, config.main_scene
		);
		
	}
	// add
	PlayingUnit& App::add(const WindowConfig& window_config, const SceneConfig& scene_config) {
		Window window(window_config);
		//window.setIcon(*_asset_manager.asset<Image>("images/parrot.png")); //TODO: move
		Scene scene(scene_config, [&](AssetHandle<EntityConfig> handle) {
			if (std::holds_alternative<uuid>(handle)) {
				return *_asset_manager.asset<EntityConfig>(std::get<uuid>(handle));
			}
			else if (std::holds_alternative<stdf::path>(handle)) {
				return *_asset_manager.asset<EntityConfig>(std::get<stdf::path>(handle));
			}
			else if (std::holds_alternative<EntityConfig>(handle)) {
				return std::get<EntityConfig>(handle);
			}
			else {
				throw std::logic_error("unexpected branch");
			}
		}, this);
		PlayingUnit unit(std::move(window), std::move(scene), this);
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
					//// draw
					//GPUContext& context = _contexts.at(&window);
					// BatchRenderer::draw(context, createBatch(scene));
					unit.window.swapBuffers();
					for (auto& e : unit.window.pollEvents()) {
						LOG_CORE_TRACE("polled event: {}", e);
						raiseEvent(e);
					}
				}
				if (total_watch.elapsed() > 10) {
					_main_unit->window.close();
				}
			}
			LOG_CORE_INFO("app '{}' terminated (gracefully)", _name);
		}
	}

	// createBatch
	Batch App::createBatch(const Scene& scene) {
		Batch batch;
		for (const Entity* entity : scene.getRenderable()) {
			const auto& render_component = entity->getComponent<RenderObjectComponent>();
			//batch.add({ render_component.mesh_uuid, render_component.material_uuid });
		}
		return batch;
	}
}