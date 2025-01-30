#pragma once
#include "window/window_config.hh"
#include "ecs/scene_config.hh"
#include "asset/asset_policy.hh"

namespace Parrot {
	// AppConfig (Asset)
	class AppConfig : public Asset {
	public:
		// (constructor) for Asset
		AppConfig() = default;
		AppConfig(const AssetPath& asset_path, AssetLocker& locker);
		template<JsonType JSON>
		AppConfig(
			const JSON& json, const AssetPath& asset_path, AssetLocker& locker
		) : Asset(asset_path) {
			loadFromJSON(json, locker);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetLocker& locker) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// main
			main_window = AssetHandle<WindowConfig>(json.at("main")[0], locker);
			main_scene = AssetHandle<SceneConfig>(json.at("main")[1], locker);
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
		AssetHandle<WindowConfig> main_window;
		AssetHandle<SceneConfig> main_scene;
		stdf::path asset_dir = ".";
		LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
	};
}