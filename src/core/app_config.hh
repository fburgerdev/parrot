#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"
#include "asset/policy.hh"

namespace Parrot {
	// AppConfig
	class AppConfig : public UUIDObject {
	public:
		// AppConfig
		AppConfig() = default;
		AppConfig(const stdf::path& config_path);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		AppConfig(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// main
			const auto& window = json.at("main")[0];
			if (window.is_number()) {
				main_window.emplace<uuid>(window);
			}
			else if (window.is_string()) {
				main_window.emplace<stdf::path>(string(window));
			}
			else {
				main_window.emplace<WindowConfig>(window);
			}
			const auto& scene = json.at("main")[1];
			if (scene.is_number()) {
				main_scene.emplace<uuid>(scene);
			}
			else if (scene.is_string()) {
				main_scene.emplace<stdf::path>(string(scene));
			}
			else {
				main_scene.emplace<SceneConfig>(scene);
			}
			// asset_dir
			if (json.contains("asset_dir")) {
				asset_dir = stdf::path(string(json.at("asset_dir")));
			}
			// (un)loading_policy
			if (json.contains("loading-policy")) {
				if (json.at("loading-policy") == "app") {
					// TODO: uncomment
					// loading_policy = LoadingPolicy::PRELOAD_APP;
				}
				else if (json.at("loading-policy") == "scene") {
					// TODO: uncomment
					// loading_policy = LoadingPolicy::PRELOAD_SCENE;
				}
				else if (json.at("loading-policy") == "lazy") {
					loading_policy = LoadingPolicy::LAZY_LOAD;
				}
			}
			if (json.contains("unloading-policy")) {
				if (json.at("unloading-policy") == "app") {
					 unloading_policy = UnloadingPolicy::UNLOAD_APP;
				}
				else if (json.at("unloading-policy") == "scene") {
					// TODO: uncomment
					// unloading_policy = UnloadingPolicy::UNLOAD_SCENE;
				}
				else if (json.at("unloading-policy") == "unused") {
					unloading_policy = UnloadingPolicy::UNLOAD_UNUSED;
				}
			}
		}

		// name, main(window/scene), asset_dir, (un)loading_policy
		string name = "App";
		Handle<WindowConfig> main_window = uuid(0);
		Handle<SceneConfig> main_scene = uuid(0);
		stdf::path asset_dir = ".";
		LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
	};
}