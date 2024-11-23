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
		AssetIndex() = default;
		AssetIndex(const stdf::path& asset_dir);
		// getUUID
		uuid getUUID(const stdf::path& path) const;
		// getPath
		const stdf::path& getPath(uuid uuid) const;
	private:
		Map<stdf::path, uuid> _uuids;
		Map<uuid, stdf::path> _paths;
	};

	//? is "handle" the right term?
	// AssetHandle
	template<class T>
	using AssetHandle = Variant<uuid, stdf::path, T>;

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
		//? is "handle" the right term?
		// useHandle(s)
		template<class T>
		void useHandle(auto&& func, const AssetHandle<T>& handle) {
			if (std::holds_alternative<uuid>(handle)) {
				func(*asset<T>(std::get<uuid>(handle)));
			}
			else if (std::holds_alternative<stdf::path>(handle)) {
				func(*asset<T>(std::get<stdf::path>(handle)));
			}
			else {
				func(std::get<T>(handle));
			}
		}
		template<class TFirst, class... TRest>
		void useHandles(auto&& func, const AssetHandle<TFirst>& first, const AssetHandle<TRest>&... rest) {
			useHandle<TFirst>([&](const TFirst& value) {
				if constexpr (sizeof...(TRest) > 0) {
					useHandles([=](const TRest&... rest) {
						func(value, rest...);
					}, rest...);
				}
				else {
					func(value);
				}
			}, first);
		}
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
		AssetIndex _index;
		Map<uuid, Asset> _assets;
	};
}