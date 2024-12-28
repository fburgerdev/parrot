#pragma once
#include "handle.hh"
#include "asset_resource.hh"
#include "asset_view.hh"
#include "asset_index.hh"
#include "asset_policy.hh"

namespace Parrot {
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
			return AssetView<T>(_assets.at(uuid), [&, uuid] {
				_assets.erase(uuid);
			});
		}
		template<class T>
		AssetView<T> asset(const stdf::path& filepath) {
			return asset<T>(_index.getUUID(filepath));
		}
		template<class T>
		AssetView<T> asset(const Handle<T>& handle) {
			if (std::holds_alternative<uuid>(handle)) {
				return asset<T>(std::get<uuid>(handle));
			}
			else if (std::holds_alternative<stdf::path>(handle)) {
				return asset<T>(std::get<stdf::path>(handle));
			}
			else {
				return {};
			}
		}

		// isLoaded
		bool isLoaded(uuid uuid) const;
		bool isLoaded(const stdf::path& path) const;
		bool isLoaded(const Variant<uuid, stdf::path>& variant) const;

		// getHandleResolver
		HandleResolver getHandleResolver();
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
		AssetIndex _index;
		Map<uuid, AssetResource> _assets;
	};
}