#pragma once
#include "scene.hh"

namespace Parrot {
	// None
	struct None {};
	
	// WindowConfig
	class WindowConfig {
	public:
		// WindowConfig
		template<class JSON>
		WindowConfig(const JSON& json) {
			// title
			if (json.contains("title")) {
				title = string(json.at("title"));
			}
			// width, height
			if (json.contains("size")) {
				width = uint(json.at("size")[0]);
				height = uint(json.at("size")[1]);
			}
			// scene
			if (scene.at("scene").is_number()) {
				scene = uuid(json.at("scene"));
			}
			else if (scene.at("scene").is_string()) {
				scene = stdf::path(string(json.at("scene")));
			}
			else {
				scene = SceneConfig(json.at("scene"));
			}
		}

		// title, width, height, scene
		string title = "Untitled Window";
		uint width = 1080, height = 720;
		Variant<None, uuid, stdf::path, SceneConfig> scene = None();
	};
}