#pragma once
#include "uuid.hh"

namespace Parrot {
	// AssetIndex
	class AssetIndex {
	public:
		// AssetIndex
		AssetIndex() = default;
		AssetIndex(const stdf::path& asset_dir);

		// getUUID
		uuid getUUID(const stdf::path& path) const;
		// getPath
		const stdf::path& getPath(uuid id) const;
	private:
		stdf::path _asset_dir;
		Map<stdf::path, uuid> _uuids;
		Map<uuid, stdf::path> _paths;
	};
}