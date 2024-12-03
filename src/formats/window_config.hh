#pragma once
#include "common.hh"

namespace Parrot {
	// None
	struct None {};
	
	// WindowConfig
	class WindowConfig {
	public:
		// WindowConfig
		WindowConfig() = default;
		WindowConfig(const stdf::path& config_path);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		WindowConfig(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			// title
			if (json.contains("title")) {
				title = string(json.at("title"));
			}
			// width, height
			if (json.contains("size")) {
				width = uint(json.at("size")[0]);
				height = uint(json.at("size")[1]);
			}
		}

		// title, width, height
		string title = "Untitled Window";
		uint width = 1080, height = 720;
	};
}