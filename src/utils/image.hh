#pragma once
#include "core/uuid.hh"

namespace Parrot {
	// ImageFormat
	enum class ImageFormat {
		NONE = 0, GRAY, RGB, RGBA
	};

	// Image
	class Image : public UUIDObject {
	public:
		// Image
		Image() = default;
		Image(const stdf::path& filepath);
		Image(const Image& other);
		Image(Image&& other) noexcept;
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Image(const JSON& json, const stdf::path& filepath) {}
		// ~Image
		~Image();
		// =
		Image& operator=(const Image& other);
		Image& operator=(Image&& other) noexcept;

		// getWidth
		uint getWidth() const;
		// getHeight
		uint getHeight() const;
		// getFormat
		ImageFormat getFormat() const;
		// getBytes
		const uchar* getBytes() const;
	private:
		uint _width = 0, _height = 0;
		ImageFormat _format = ImageFormat::NONE;
		uchar* _bytes = nullptr;
	};
}