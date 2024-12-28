#pragma once
#include "asset_handle.hh"
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
		AssetView<T> asset(uuid id) {
			if (!_assets.contains(id)) {
				stdf::path path = _asset_dir / _index.getPath(id);
				bool destroy_if_unviewed = (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED);
				_assets.emplace(id, makeAsset<T>(path, destroy_if_unviewed));
			}
			return AssetView<T>(_assets.at(id), [&, id] {
				_assets.erase(id);
			});
		}
		template<class T>
		AssetView<T> asset(const stdf::path& filepath) {
			if (_index.isIndexed(filepath)) {
				return asset<T>(_index.getUUID(filepath));
			}
			else {
				stdf::path path = _asset_dir / filepath;
				bool destroy_if_unviewed = (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED);
				auto asset = makeAsset<T>(path, destroy_if_unviewed);
				uuid id = ((T*)asset.get())->getUUID();
				_index.index(filepath, id);
				_assets.emplace(id, std::move(asset));
				return AssetView<T>(_assets.at(id), [&, id] {
					_assets.erase(id);
				});
			}
		}
		template<class T>
		AssetView<T> asset(const AssetHandle<T>& handle) {
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
		bool isLoaded(uuid id) const;
		bool isLoaded(const stdf::path& path) const;
		bool isLoaded(const Variant<uuid, stdf::path>& variant) const;

		// getHandleResolver
		AssetHandleResolver getHandleResolver();
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
		AssetIndex _index;
		Map<uuid, AssetResource> _assets;
	};
}