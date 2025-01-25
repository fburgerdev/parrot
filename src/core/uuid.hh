#pragma once
#include "common.hh"

namespace Parrot {
	// UUID
	using UUID = uint64;
	// generateUUID
	UUID generateUUID();

	// UUIDObject
	class UUIDObject {
	public:
		// UUIDObject
		UUIDObject();
		UUIDObject(UUID uuid);
		UUIDObject(const stdf::path& filepath);
		UUIDObject(const UUIDObject& other);
		UUIDObject(UUIDObject&& other) noexcept;
		// =
		UUIDObject& operator=(const UUIDObject& other);
		UUIDObject& operator=(UUIDObject&& other) noexcept;
		// getUUID
		UUID getUUID() const;
	private:
		UUID _uuid;
	};
}