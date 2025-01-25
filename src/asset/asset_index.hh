#pragma once
#include "core/uuid.hh"

namespace Parrot {
	// AssetIndex
	class AssetIndex {
	public:
		// AssetIndex
		AssetIndex() = default;
		AssetIndex(const stdf::path& asset_dir);

		// index
		void index(const stdf::path& path, UUID uuid);
		// isIndexed
		bool isIndexed(const stdf::path& path) const;
		bool isIndexed(UUID uuid) const;

		// get
		// :: uuid
		UUID getUUID(const stdf::path& path) const;
		// :: path
		const stdf::path& getPath(UUID uuid) const;
	private:
		stdf::path _asset_dir;
		Map<stdf::path, UUID> _uuids;
		Map<UUID, stdf::path> _paths;
	};
}