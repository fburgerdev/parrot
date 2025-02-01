#include "common.hh"
#include "image.hh"
#include "core/log.hh"
#include <stb/stb_image.hh>
#include <stb/stb_image_write.hh>

namespace Parrot {
  // (constructor)
  Image::Image(const stdf::path& filepath, Opt<stdf::path> debug_root)
    : _width(0), _height(0), _format(ImageFormat::NONE), _bytes(nullptr) {
    int width, height, channels;
    uchar* img = stbi_load(
      filepath.string().c_str(), &width, &height, &channels, 4
    );
    if (!img) {
      LOG_ASSET_ERROR(
        "failed to load image {}", getDebugFilepath(filepath, debug_root)
      );
      LOG_ASSET_ERROR("stb-image error message:\n{}", stbi_failure_reason());
      return;
    }
    switch (channels) {
    case 1:
      _format = ImageFormat::GRAY;
      break;
    case 3:
      _format = ImageFormat::RGB;
      break;
    case 4:
      _format = ImageFormat::RGBA;
      break;
    default:
      LOG_ASSET_ERROR(
        "failed to load image {}"
        "due to unsupported image format with {} channels",
        getDebugFilepath(filepath, debug_root), channels
      );
      return;
    }
    _width = width;
    _height = height;
    _bytes = img;
    LOG_ASSET_DEBUG(
      "loaded image {}, {}px x {}px with {} channels",
      getDebugFilepath(filepath, debug_root), width, height, channels
    );
  }
  Image::Image(const AssetPath& asset_path, AssetAPI& asset_api)
    : Image(asset_path.file, asset_path.debug_root) {}
  Image::Image(strview name, const uchar* buffer, usize size)
      : _name(name), _width(0), _height(0),
      _format(ImageFormat::NONE), _bytes(nullptr) {
    int width, height, channels;
    uchar* img = stbi_load_from_memory(
      buffer, size, &width, &height, &channels, 4
    );
    if (!img) {
      LOG_ASSET_ERROR("failed to load image {} (from buffer)", name);
      LOG_ASSET_ERROR("stb-image error message:\n{}", stbi_failure_reason());
      return;
    }
    switch (channels) {
    case 1:
      _format = ImageFormat::GRAY;
      break;
    case 3:
      _format = ImageFormat::RGB;
      break;
    case 4:
      _format = ImageFormat::RGBA;
      break;
    default:
      LOG_ASSET_ERROR(
        "failed to load image {} (from buffer)"
        "due to unsupported image format with {} channels",
        name, channels
      );
      return;
    }
    _width = width;
    _height = height;
    _bytes = img;
    LOG_ASSET_DEBUG(
      "loaded image {} (from buffer), {}px x {}px with {} channels",
      name, width, height, channels
    );
  }
  Image::Image(const Image& other)
    : _width(other._width), _height(other._height), _format(other._format) {
    usize size = _width * _height;
    switch (_format) {
    case Parrot::ImageFormat::GRAY:
      size *= 1;
      break;
    case Parrot::ImageFormat::RGB:
      size *= 3;
      break;
    case Parrot::ImageFormat::RGBA:
      size *= 4;
      break;
    default:
      break;
    }
    _bytes = (uchar*)memcpy(new uchar[size], other._bytes, size);
  }
  Image::Image(Image&& other) noexcept
    : _width(std::exchange(other._width, 0)),
      _height(std::exchange(other._height, 0)),
      _format(std::exchange(other._format, ImageFormat::NONE)),
      _bytes(std::exchange(other._bytes, nullptr)) {}
  // (destructor)
  Image::~Image() {
    stbi_image_free(_bytes);
  }
  // (assignment)
  Image& Image::operator=(const Image& other) {
    _width = other._width;
    _height = other._height;
    _format = other._format;
    usize size = _width * _height;
    switch (_format) {
    case Parrot::ImageFormat::GRAY:
      size *= 1;
      break;
    case Parrot::ImageFormat::RGB:
      size *= 3;
      break;
    case Parrot::ImageFormat::RGBA:
      size *= 4;
      break;
    default:
      break;
    }
    stbi_image_free(_bytes);
    _bytes = (uchar*)memcpy(new uchar[size], other._bytes, size);
    return *this;
  }
  Image& Image::operator=(Image&& other) noexcept {
    _width = std::exchange(other._width, 0);
    _height = std::exchange(other._height, 0);
    _format = std::exchange(other._format, ImageFormat::NONE);
    _bytes = std::exchange(other._bytes, nullptr);
    return *this;
  }

  // safeAs
  // :: bmp
  void Image::safeAsBMP(
    const stdf::path& filepath, Opt<stdf::path> debug_root
  ) const {
    int channels = 0;
    switch (_format) {
    case ImageFormat::GRAY:
      channels = 1;
      break;
    case ImageFormat::RGB:
      channels = 3;
      break;
    case ImageFormat::RGBA:
      channels = 4;
      break;
    default:
      break;
    }
    int error_code = stbi_write_bmp(
      (const char*)filepath.c_str(),
      _width, _height, channels, _bytes
    );
    if (error_code == 0) {
      LOG_ASSET_ERROR(
        "failed to safe image {} at {}, could not open file",
        _name, getDebugFilepath(filepath, debug_root)
      );
    }
    else if (error_code != 1) {
      LOG_ASSET_ERROR(
        "failed to safe image {} at {}, invalid image data",
        _name, getDebugFilepath(filepath, debug_root)
      );
    }
    else {
      LOG_ASSET_DEBUG("successfully safed image {} at {}",
        _name, getDebugFilepath(filepath, debug_root)
      );
    }
  }

  // get
  // :: width
  uint Image::getWidth() const {
    return _width;
  }
  // :: height
  uint Image::getHeight() const {
    return _height;
  }
  // :: format
  ImageFormat Image::getFormat() const {
    return _format;
  }
  // :: bytes
  const uchar* Image::getBytes() const {
    return _bytes;
  }

  // getDebugFilepath
  stdf::path Image::getDebugFilepath(
    const stdf::path& filepath, Opt<stdf::path> debug_root
  ) {
    if (debug_root) {
      return stdf::relative(filepath, *debug_root);
    }
    else {
      return filepath;
    }
  }
}