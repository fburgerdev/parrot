#pragma once
#include "image.hh"

namespace Parrot {
	// Texture
	class Texture : public UUIDObject {
	public:
		// Texture
		Texture(const stdf::path& filepath);
		
		// image_uuid
		uuid image_uuid;
	};
}