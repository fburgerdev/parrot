#pragma once
#include "window.hh"
#include "asset/policy.hh"

namespace Parrot {
	// AppConfig
	class AppConfig {
	public:
		// AppConfig
		template<class JSON>
		AppConfig(const JSON& json) {
			// name
			if (json.contains("name")) {
				name = string(json.at("name"));
			}
			// main
			if (json.at("main").is_number()) {
				main = uuid(json.at("main"));
			}
			else if (json.at("main").is_string()) {
				main = stdf::path(json.at("main"));
			}
			else {
				main = WindowConfig(json.at("main"));
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

		// name, main, (un)loading_policy
		string name = "App";
		Variant<uuid, stdf::path, WindowConfig> main;
		LoadingPolicy loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy unloading_policy = UnloadingPolicy::UNLOAD_APP;
	};
}