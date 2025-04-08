#pragma once
#include "core/asset_handle.hh"
#include "core/log.hh"

namespace Parrot {
  enum class ImageFormat {
    NONE = 0, GRAY, RGB, RGBA
  };

  /*
    Image
    supported formats: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
  */
  class Image : public Asset {
  public:
    Image(const stdf::path& filepath, Opt<stdf::path> debug_root = {});
    Image(strview name, const uchar* buffer, usize size);
    Image(const Image& other);
    Image(Image&& other) noexcept;
    Image(const AssetPath& path, AssetAPI& api);
    Image(const SerialNode& node, const AssetPath& path, AssetAPI& api);
    ~Image();
    Image& operator=(const Image& other);
    Image& operator=(Image&& other) noexcept;

    void safeAsBMP(
      const stdf::path& filepath, Opt<stdf::path> debug_root = {}
    ) const;

    uint getWidth() const;
    uint getHeight() const;
    ImageFormat getFormat() const;
    const uchar* getBytes() const;
  private:
    static stdf::path getDebugFilepath(
      const stdf::path& filepath, Opt<stdf::path> debug_root = {}
    );
    
    string _name;
    uint _width = 0, _height = 0;
    ImageFormat _format = ImageFormat::NONE;
    uchar* _bytes = nullptr;
  };
}