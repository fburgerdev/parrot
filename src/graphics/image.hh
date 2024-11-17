#pragma once
#include "uuid.hh"

namespace Parrot {
	// ImageFormat
	enum class ImageFormat {
		NONE = 0, GRAY, RGB, RGBA
	};

	// Image
	class Image : public UUIDObject {
	public:
		// Image
		Image(const stdf::path& filepath);

		// getWidth
		uint getWidth() const;
		// getHeight
		uint getHeight() const;
		// getFormat
		ImageFormat getFormat() const;
		// getBytes
		const uchar* getBytes() const;
	private:
		uint _width, _height;
		ImageFormat _format;
		uchar* _bytes;
	};
}