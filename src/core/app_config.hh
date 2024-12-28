#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"
#include "asset/asset_policy.hh"

namespace Parrot {
	// AppConfig
	class AppConfig : public UUIDObject {
	public:
		// AppConfig
		AppConfig() = default;
		AppConfig(const stdf::path& config_path);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		AppConfig(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, [[maybe_unused]] const stdf::path& filepath) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// main
			main_window = parseHandleFromJSON<WindowConfig>(json.at("main")[0], filepath);
			main_scene = parseHandleFromJSON<SceneConfig>(json.at("main")[1], filepath);
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
		Handle<WindowConfig> main_window;
		Handle<SceneConfig> main_scene;
		stdf::path asset_dir = ".";
		LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
	};
}