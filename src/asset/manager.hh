#pragma once
#include "uuid.hh"
#include "asset.hh"
#include "view.hh"
#include "policy.hh"

namespace Parrot {
	// AssetIndex
	class AssetIndex {
	public:
		// AssetIndex
		AssetIndex(const stdf::path& asset_dir);
		// getUUID
		uuid getUUID(const stdf::path& path) const;
		// getPath
		const stdf::path& getPath(uuid uuid) const;
	private:
		Map<stdf::path, uuid> _uuids;
		Map<uuid, stdf::path> _paths;
	};

	// AssetManager
	class AssetManager {
	public:
		// AssetManager
		AssetManager() = default;
		AssetManager(const stdf::path& asset_dir);
		AssetManager(
			const stdf::path& asset_dir,
			LoadingPolicy loading_policy,
			UnloadingPolicy unloading_policy
		);
		
		// asset
		template<class T>
		AssetView<T> asset(uuid uuid) {
			if (!_assets.contains(uuid)) {
				stdf::path path = _asset_dir / _index.getPath(uuid);
				bool destroy_if_unviewed = (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED);
				_assets.emplace(uuid, makeAsset<T>(path, destroy_if_unviewed));
			}
			return _assets.at(uuid);
		}
		template<class T>
		AssetView<T> asset(const stdf::path& filepath) {
			return asset<T>(_index.getUUID(filepath));
		}
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy;
		UnloadingPolicy _unloading_policy;
		AssetIndex _index;
		Map<uuid, Asset> _assets;
	};
}