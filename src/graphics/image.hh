#pragma once
#include "core/asset_handle.hh"
#include "core/log.hh"

namespace Parrot {
  // ImageFormat
  enum class ImageFormat {
    NONE = 0, GRAY, RGB, RGBA
  };

  /*
    Image
    supported formats: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
  */
  class Image : public Asset {
  public:
    // (constructor)
    Image(const stdf::path& filepath, Opt<stdf::path> debug_root = {});
    Image(strview name, const uchar* buffer, usize size);
    Image(const Image& other);
    Image(Image&& other) noexcept;
    // :: for Asset
    Image(const AssetPath& path, AssetAPI& api);
    Image(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      LOG_ASSET_ERROR("this method only exists to implement the asset-api");
    }
    // (destructor)
    ~Image();
    // (assignment)
    Image& operator=(const Image& other);
    Image& operator=(Image&& other) noexcept;

    // safeAs
    // :: bmp
    void safeAsBMP(
      const stdf::path& filepath, Opt<stdf::path> debug_root = {}
    ) const;

    // get
    // :: width
    uint getWidth() const;
    // :: height
    uint getHeight() const;
    // :: format
    ImageFormat getFormat() const;
    // :: bytes
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