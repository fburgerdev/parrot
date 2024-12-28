#pragma once
#include "handle.hh"
#include "utils/image.hh"

namespace Parrot {
	// TextureWrap
	enum class TextureWrap {
		CLAMP_TO_EDGE, CLAMP_TO_BORDER, REPEAT, MIRRORED_REPEAT
	};
	// TextureFilter
	enum class TextureFilter {
		LINEAR, NEAREST
	};
	// Mipmap
	enum class Mipmap {
		NONE, LINEAR, NEAREST
	};

	// TextureConfig
	class TextureConfig : public UUIDObject {
	public:
		// TextureConfig
		TextureConfig(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		TextureConfig(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, const stdf::path& filepath) {
			//TODO: properties...
			image = parseHandleFromJSON<Image>(json.at("image"), filepath);
		}
		
		// hor_wrap, ver_wrap, mag_filter, min_filter, mipmap, image
		TextureWrap hor_wrap = TextureWrap::CLAMP_TO_EDGE, ver_wrap = TextureWrap::CLAMP_TO_EDGE;
		TextureFilter mag_filter = TextureFilter::LINEAR, min_filter = TextureFilter::LINEAR;
		Mipmap mipmap = Mipmap::NONE;
		Handle<Image> image;
	};
}