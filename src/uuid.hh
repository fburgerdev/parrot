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
		UUIDObject(const stdf::path& asset_path);
		UUIDObject(const UUIDObject& other);
		UUIDObject(UUIDObject&& other) noexcept;
		// =
		UUIDObject& operator=(const UUIDObject&) = delete;
		UUIDObject& operator=(UUIDObject&& other) = delete;
		// getUUID
		uuid getUUID() const;
	private:
		uuid _uuid;
	};
}