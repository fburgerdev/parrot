#pragma once
#include "core/asset_handle.hh"
#include "image.hh"

namespace Parrot {
  enum class TextureWrap {
    CLAMP_TO_EDGE, CLAMP_TO_BORDER, REPEAT, MIRRORED_REPEAT
  };
  enum class TextureFilter {
    LINEAR, NEAREST
  };
  enum class Mipmap {
    NONE, LINEAR, NEAREST
  };

  class TextureConfig : public Asset {
  public:
    TextureConfig(AssetHandle<Image> image);
    TextureConfig(const AssetPath& path, AssetAPI& api);
    TextureConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    
    TextureWrap hor_wrap = TextureWrap::CLAMP_TO_EDGE;
    TextureWrap ver_wrap = TextureWrap::CLAMP_TO_EDGE;
    TextureFilter mag_filter = TextureFilter::LINEAR;
    TextureFilter min_filter = TextureFilter::LINEAR;
    Mipmap mipmap = Mipmap::NONE;
    AssetHandle<Image> image;
  };
}