#pragma once
#include "core/asset_handle.hh"
#include "image.hh"

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
      image = AssetHandle<Image>(json.at("image"), asset_api);
      // TODO: properties...
    }
    
    // (hor/ver)wrap, (mag/min)filter, mipmap, image
    TextureWrap hor_wrap = TextureWrap::CLAMP_TO_EDGE;
    TextureWrap ver_wrap = TextureWrap::CLAMP_TO_EDGE;
    TextureFilter mag_filter = TextureFilter::LINEAR;
    TextureFilter min_filter = TextureFilter::LINEAR;
    Mipmap mipmap = Mipmap::NONE;
    AssetHandle<Image> image;
  };
}