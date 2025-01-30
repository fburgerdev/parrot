#pragma once
#include "core/asset_handle.hh"
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

	// TextureConfig (Asset)
	class TextureConfig : public Asset {
	public:
		// (constructor) for Asset
		TextureConfig(const AssetPath& asset_path, AssetAPI& asset_api);
		TextureConfig(AssetHandle<Image> image);
		template<JsonType JSON>
		TextureConfig(
			const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
		) : Asset(asset_path) {
			loadFromJSON(json, asset_api);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
			//TODO: properties...
			image = AssetHandle<Image>(json.at("image"), asset_api);
		}
		
		// hor_wrap, ver_wrap, mag_filter, min_filter, mipmap, image
		TextureWrap hor_wrap = TextureWrap::CLAMP_TO_EDGE, ver_wrap = TextureWrap::CLAMP_TO_EDGE;
		TextureFilter mag_filter = TextureFilter::LINEAR, min_filter = TextureFilter::LINEAR;
		Mipmap mipmap = Mipmap::NONE;
		AssetHandle<Image> image;
	};
}