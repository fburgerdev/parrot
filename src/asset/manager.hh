#pragma once
#include "handle.hh"
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

		// isLoaded
		bool isLoaded(uuid uuid) const {
			return _assets.contains(uuid);
		}
		bool isLoaded(const stdf::path& path) const {
			return _assets.contains(_index.getUUID(path));
		}
		bool isLoaded(const Variant<uuid, stdf::path>& variant) const {
			return std::visit([&](const auto& value) {
				return isLoaded(value);
			}, variant);
		}

		// getHandleResolver
		HandleResolver getHandleResolver() {
			return HandleResolver([&](
				const Variant<uuid, stdf::path>& variant,
				const function<Pair<void*, function<void()>>(stdf::path)>& create,
				const function<void(const void*)>& callback) {
				uuid deduced_uuid = std::holds_alternative<uuid>(variant) ? std::get<uuid>(variant) : _index.getUUID(std::get<stdf::path>(variant));
				if (!isLoaded(deduced_uuid)) {
					auto [value, delete_func] = create(_asset_dir / _index.getPath(deduced_uuid));
					_assets.emplace(deduced_uuid, Asset(value, (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED), delete_func));
				}
				callback(_assets.at(deduced_uuid).get());
			});
		}
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
		AssetIndex _index;
		Map<uuid, Asset> _assets;
	};
}