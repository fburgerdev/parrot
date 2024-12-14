#pragma once
#include "common.hh"

namespace Parrot {
	// uuid
	using uuid = uint64;
	// generateUUID
	uuid generateUUID();

	// UUIDObject
	class UUIDObject {
	public:
		// UUIDObject
		UUIDObject();
		UUIDObject(uuid uuid);
		UUIDObject(const stdf::path& filepath);
		UUIDObject(const UUIDObject&) = delete;
		UUIDObject(UUIDObject&& other) noexcept;
		// =
		UUIDObject& operator=(const UUIDObject&) = delete;
		UUIDObject& operator=(UUIDObject&& other) noexcept;
		// getUUID
		uuid getUUID() const;
	private:
		uuid _uuid;
	};
}