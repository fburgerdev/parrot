#pragma once
#include "core/asset_handle.hh"

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
		// Image
		Image() = default;
		Image(const stdf::path& filepath);
		Image(strview name, const uchar* buffer, usize size);
		Image(const Image& other);
		Image(Image&& other) noexcept;
		Image(const AssetPath& asset_path, AssetLocker& locker);
		template<JsonType JSON>
		Image(const JSON& json, const AssetPath& asset_path, AssetLocker& locker)
      : Asset(asset_path) {}
		// ~Image
		~Image();
		// =
		Image& operator=(const Image& other);
		Image& operator=(Image&& other) noexcept;

		// safeAsBMP
		void safeAsBMP(const stdf::path& filepath) const;
		// getWidth
		uint getWidth() const;
		// getHeight
		uint getHeight() const;
		// getFormat
		ImageFormat getFormat() const;
		// getBytes
		const uchar* getBytes() const;
	private:
		string _name;
		uint _width = 0, _height = 0;
		ImageFormat _format = ImageFormat::NONE;
		uchar* _bytes = nullptr;
	};
}