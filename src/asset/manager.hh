#pragma once
#include "asset.hh"
#include "view.hh"

namespace Parrot {
	// LoadingPolicy
	enum class LoadingPolicy {
		/* PRELOAD_APP, PRELOAD_SCENE, */ LAZY_LOAD
	};
	// UnloadingPolicy
	enum class UnloadingPolicy {
		UNLOAD_APP, /* UNLOAD_SCENE, */ UNLOAD_UNUSED
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
		
		// getAsset
		template<class T>
		AssetView<T> getAsset(const stdf::path& filepath) {
			stdf::path canonical_path = stdf::canonical(_asset_dir / filepath);
			usize hash_key = std::hash<stdf::path>()(canonical_path); //! hash not unique identifier
			if (!_assets.contains(hash_key)) {
				bool destroy_if_unviewed = (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED);
				_assets.emplace(hash_key, makeAsset<T>(canonical_path, destroy_if_unviewed));
			}
			return AssetView<T>(_assets.at(hash_key), [&, hash_key] {
				_assets.erase(hash_key);
			});
		}
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
		Map<usize, Asset> _assets;
	};
}