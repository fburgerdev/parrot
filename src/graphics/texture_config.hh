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
    // (constructor)
    TextureConfig(AssetHandle<Image> image);
    // :: for Asset
    TextureConfig(const AssetPath& path, AssetAPI& api);
    template<JsonType JSON>
    TextureConfig(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      image = AssetHandle<Image>(json.at("image"), api);
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