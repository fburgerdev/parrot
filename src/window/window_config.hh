#pragma once
#include "debug/debug.hh"

namespace Parrot {
	// CursorState
	enum class CursorState {
		NORMAL, HIDDEN, CAPTURED
	};

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
			// cursor
			if (json.contains("cursor")) {
				if (json.at("cursor") == "normal") {
					cursor = CursorState::NORMAL;
				}
				else if (json.at("cursor") == "hidden") {
					cursor = CursorState::HIDDEN;
				}
				else if (json.at("cursor") == "captured") {
					cursor = CursorState::CAPTURED;
				}
				else {
					LOG_ASSET_WARNING("invalid window-config value {} for key 'cursor', defaults to 'normal'", json.at("cursor"));
		}

		// title, width, height, cursor
		string title = "Untitled Window";
		uint width = 1080, height = 720;
		CursorState cursor = CursorState::NORMAL;
	};
}