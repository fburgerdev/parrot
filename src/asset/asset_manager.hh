#pragma once
#include "core/asset_handle.hh"
#include "asset_resource.hh"
#include "asset_registry.hh"
#include "asset_view.hh"
#include "asset_index.hh"
#include "asset_policy.hh"

namespace Parrot {
	// AssetManager
	class AssetManager : public AssetLocker {
	public:
		// AssetManager
		AssetManager() = default;
		AssetManager(const stdf::path& asset_dir);
		AssetManager(
			const stdf::path& asset_dir,
			LoadingPolicy loading_policy,
			UnloadingPolicy unloading_policy
		);
		
		// getAssetDirectory
		const stdf::path getAssetDirectory() const;

    // // lockAsset
    // template<class T>
    // SharedPtr<T> lockAsset(UUID uuid) {
    //   auto it = _loaded.find(uuid);
    //   if (it == _loaded.end()) {
    //     auto shared = std::make_shared<T>(
    //       _registry.getAssetPath(uuid), createAssetResolver()
    //     );
    //     if (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED) {
    //       _loaded.emplace(uuid, WeakPtr<T>(shared));
    //     }
    //     else {
    //       _loaded.emplace(uuid, SharedPtr<T>(shared));
    //     }
    //     return shared;
    //   }
    //   else {
    //     if (std::holds_alternative<SharedPtr<T>>(it->second)) {
    //       return std::get<SharedPtr<T>>(it->second);
    //     }
    //     else {
    //       auto weak_ptr = std::get<WeakPtr<T>>(it->second);
    //       if (weak_ptr.expired()) {
    //         auto shared = std::make_shared<T>(
    //           _registry.getAssetPath(uuid), createAssetResolver()
    //         );
    //         if (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED) {
    //           _loaded.emplace(uuid, WeakPtr<T>(shared));
    //         }
    //         else {
    //           _loaded.emplace(uuid, SharedPtr<T>(shared));
    //         }
    //         _loaded.insert(it, shared);
    //         return shared;
    //       }
    //       else {
    //         return weak_ptr.lock();
    //       }
    //     }
    //   }
    //   return SharedPtr<T>(nullptr);
    // }
    // template<class T>
    // SharedPtr<T> lockAsset(const AssetPath& asset_path) {
    //   return lockAsset<T>(_registry.getUUID(asset_path));
    // }
    // template<class T>
    // SharedPtr<T> lockAsset(const AssetKey& key) {
    //   return std::visit([&] (const auto& alt) {
    //     return lockAsset<T>(alt);
    //   }, key);
    // }

    virtual SharedPtr<Asset> lock(const AssetKey& key, Func<SharedPtr<Asset>(const AssetPath&)> func) override {
      UUID uuid = _registry.getUUID(key);
      AssetPath asset_path = _registry.getAssetPath(key);
      asset_path.filepath = _asset_dir / asset_path.filepath;
      auto it = _loaded.find(uuid);
      if (it == _loaded.end()) {
        auto asset = func(asset_path);
        _loaded.emplace(uuid, SharedPtr<Asset>(asset));
        return asset;
      }
      else {
        if (std::holds_alternative<SharedPtr<Asset>>(it->second)) {
          return std::get<SharedPtr<Asset>>(it->second);
        }
        else if (!std::get<WeakPtr<Asset>>(it->second).expired()) {
          return std::get<WeakPtr<Asset>>(it->second).lock();
        }
        else {
          auto asset = func(asset_path);
          it->second = SharedPtr<Asset>(asset);
          return asset;
        }
      }
    }
    virtual void add(UUID uuid, const AssetPath& asset_path, SharedPtr<Asset> asset) override {
      _registry.add(uuid, asset_path);
      _loaded.emplace(uuid, asset);
    }

    // // loadedAsset
    // bool loadedAsset(const AssetKey& key) const {
    //   return _loaded.contains(_registry.getUUID(key));
    // }
    // getAsset
    // template<class T = Asset>
    // SharedPtr<T> getAsset(const AssetKey& key) {
    //   return _loaded.at(_registry.getUUID(key));
    // }
    // // registerAsset
    // SharedPtr<Asset> registerAsset(const AssetPath& asset_path, SharedPtr<Asset> asset) {
    //   if (!_registry.contains(asset_path)) {
    //     _registry.add(asset_path);
    //   }
    //   if (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED) {
    //     _loaded.emplace(_registry.getUUID(asset_path), WeakPtr<Asset>(asset));
    //   }
    //   else {
    //     _loaded.emplace(_registry.getUUID(asset_path), SharedPtr<Asset>(asset));
    //   }
    //   return asset;
    // }
		// // asset
		// template<class T>
		// AssetView<T> asset(UUID uuid) {
		// 	if (!_assets.contains(uuid)) {
		// 		stdf::path path = _asset_dir / _index.getPath(uuid);
		// 		bool destroy_if_unviewed = (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED);
		// 		_assets.emplace(uuid, makeAsset<T>(path, destroy_if_unviewed));
		// 	}
		// 	return AssetView<T>(_assets.at(uuid), [&, uuid] {
		// 		_assets.erase(uuid);
		// 	});
		// }
		// template<class T>
		// AssetView<T> asset(const stdf::path& filepath) {
		// 	if (_index.isIndexed(filepath)) {
		// 		return asset<T>(_index.getUUID(filepath));
		// 	}
		// 	else {
		// 		stdf::path path = _asset_dir / filepath;
		// 		bool destroy_if_unviewed = (_unloading_policy == UnloadingPolicy::UNLOAD_UNUSED);
		// 		auto asset = makeAsset<T>(path, destroy_if_unviewed);
		// 		UUID uuid = ((T*)asset.get())->getUUID();
		// 		_index.index(filepath, uuid);
		// 		_assets.emplace(uuid, std::move(asset));
		// 		return AssetView<T>(_assets.at(uuid), [&, uuid] {
		// 			_assets.erase(uuid);
		// 		});
		// 	}
		// }
		// template<class T>
		// AssetView<T> asset(const AssetHandle<T>& handle) {
		// 	if (std::holds_alternative<UUID>(handle)) {
		// 		return asset<T>(std::get<UUID>(handle));
		// 	}
		// 	else if (std::holds_alternative<stdf::path>(handle)) {
		// 		return asset<T>(std::get<stdf::path>(handle));
		// 	}
		// 	else {
		// 		return {};
		// 	}
		// }

		// // isLoaded
		// bool isLoaded(UUID uuid) const;
		// bool isLoaded(const stdf::path& path) const;
		// bool isLoaded(const Variant<UUID, stdf::path>& variant) const;

		// createAssetResolver
		AssetResolver createAssetResolver();
	private:
		stdf::path _asset_dir;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
		// AssetIndex _index;
    AssetRegistry _registry;
		// Map<UUID, AssetResource> _assets;
    Map<UUID, Variant<SharedPtr<Asset>, WeakPtr<Asset>>> _loaded;
	};
}