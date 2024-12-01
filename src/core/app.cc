#include "common.hh"
#include "app.hh"
#include "asset/config/app_config.hh"
#include "window/window.hh"
#include "graphics/context.hh"
#include "ecs/components/render.hh"
#include "debug/debug.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
	// App
	App::App(const stdf::path& config_path) {
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
				add(window_config, scene_config);
			}, config.main_window, config.main_scene
		);
		_main_window = &_windows.begin()->second;
	}
	// add
	void App::add(const WindowConfig& window_config, const SceneConfig& scene_config) {
		Window window(window_config);
		window.setIcon(*_asset_manager.asset<Image>("images/parrot.png"));
		Scene scene(scene_config, [&](Variant<uuid, stdf::path, EntityConfig> entity_id) {
			if (std::holds_alternative<uuid>(entity_id)) {
				return *_asset_manager.asset<EntityConfig>(std::get<uuid>(entity_id));
			}
			else if (std::holds_alternative<stdf::path>(entity_id)) {
				return *_asset_manager.asset<EntityConfig>(std::get<stdf::path>(entity_id));
			}
			else if (std::holds_alternative<EntityConfig>(entity_id)) {
				return std::get<EntityConfig>(entity_id);
			}
		});
		_window_scene_pairs.emplace(window.getUUID(), scene.getUUID());
		_windows.emplace(window.getUUID(), std::move(window));
		_scenes.emplace(scene.getUUID(), std::move(scene));
	}
	// run
	void App::run() {
		if (_main_window) {
			LOG_CORE_INFO("app '{}' running", _name);
			Stopwatch total_watch, frame_watch;
			while (_main_window->isOpen()) {
				seconds delta_time = frame_watch.reset();
				LOG_CORE_TRACE("update app '{}'", _name);
				for (auto& [window_uuid, scene_uuid] : _window_scene_pairs) {
					Window& window = _windows.at(window_uuid);
					Scene& scene = _scenes.at(scene_uuid);
					// update scene
					scene.update(delta_time);
					//// draw
					//GPUContext& context = _contexts.at(&window);
					// BatchRenderer::draw(context, createBatch(scene));
					window.update();
				}
				if (total_watch.elapsed() > 3) {
					_main_window->close();
				}
			}
			LOG_CORE_INFO("app '{}' terminated (gracefully)", _name);
		}
	}

	// createBatch
	Batch App::createBatch(const Scene& scene) {
		Batch batch;
		for (const Entity* entity : scene.getRenderable()) {
			const auto& render_component = entity->getComponent<RenderComponent>();
			//batch.add({ render_component.mesh_uuid, render_component.material_uuid });
		}
		return batch;
	}
}