#include "common.hh"
#include "image.hh"
#include "debug/debug.hh"
#include "stb/stb_image.hh"

namespace Parrot {
	// Image
	Image::Image(const stdf::path& filepath)
		: _width(0), _height(0), _format(ImageFormat::NONE), _bytes(nullptr) {
		// supported: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
		int width, height, channels;
		uchar* img = stbi_load(filepath.string().c_str(), &width, &height, &channels, 4);
		if (!img) {
			LOG_ASSET_ERROR("failed to load image {}", filepath);
			LOG_ASSET_ERROR("stb-image error message:\n{}", stbi_failure_reason);
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
			LOG_ASSET_ERROR("failed to load image {} due to unsupported image format with {} channels", filepath, channels);
			return;
		}
		_width = width;
		_height = height;
		_bytes = img;
		LOG_ASSET_DEBUG("loaded image {} ({}px x {}px with {} channels)", filepath, width, height, channels);
	}
	// ~Image
	Image::~Image() {
		stbi_image_free(_bytes);
	}

	// getWidth
	uint Image::getWidth() const {
		return _width;
	}
	// getHeight
	uint Image::getHeight() const {
		return _height;
	}
	// getFormat
	ImageFormat Image::getFormat() const {
		return _format;
	}
	// getBytes
	const uchar* Image::getBytes() const {
		return _bytes;
	}
}