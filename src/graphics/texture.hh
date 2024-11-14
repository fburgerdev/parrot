#pragma once
#include "image.hh"

namespace Parrot {
	// Texture
	class Texture {
	public:
		// Texture
		Texture(const stdf::path& filepath);
		
		// image_path
		stdf::path image_path;
	};
}