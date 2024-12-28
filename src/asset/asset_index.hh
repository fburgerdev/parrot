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
		void index(const stdf::path& path, uuid id);
		// isIndexed
		bool isIndexed(const stdf::path& path) const;
		bool isIndexed(uuid id) const;

		// get
		// :: uuid
		uuid getUUID(const stdf::path& path) const;
		// :: path
		const stdf::path& getPath(uuid id) const;
	private:
		stdf::path _asset_dir;
		Map<stdf::path, uuid> _uuids;
		Map<uuid, stdf::path> _paths;
	};
}