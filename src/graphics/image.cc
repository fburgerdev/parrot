#include "common.hh"
#include "image.hh"
#include "stb/stb_image.hh"

namespace Parrot {
	// Image
	Image::Image(const stdf::path& filepath)
		: _width(0), _height(0), _format(ImageFormat::NONE), _bytes(nullptr) {

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