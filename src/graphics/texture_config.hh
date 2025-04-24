#pragma once
#include "core/asset_handle.hh"
#include "image.hh"

namespace Parrot {
  class TextureConfig : public Asset {
  public:
    enum class Wrap {
      CLAMP_TO_EDGE,
      CLAMP_TO_BORDER,
      REPEAT,
      MIRRORED_REPEAT
    };
    enum class Filter {
      LINEAR,
      NEAREST
    };
    enum class Mipmap {
      NONE,
      LINEAR,
      NEAREST
    };

    TextureConfig(AssetHandle<Image> image);
    TextureConfig(const AssetPath& path, AssetAPI& api);
    TextureConfig(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    
    Wrap hor_wrap = Wrap::CLAMP_TO_EDGE;
    Wrap ver_wrap = Wrap::CLAMP_TO_EDGE;
    Filter mag_filter = Filter::LINEAR;
    Filter min_filter = Filter::LINEAR;
    Mipmap mipmap = Mipmap::NONE;
    AssetHandle<Image> image;
  };
}