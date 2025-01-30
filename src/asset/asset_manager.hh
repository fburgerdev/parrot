#pragma once
#include "core/asset_handle.hh"
#include "asset_registry.hh"
#include "asset_policy.hh"

namespace Parrot {
	// AssetManager
	class AssetManager : public AssetAPI {
	public:
		// (constructor)
		AssetManager() = default;
		AssetManager(const stdf::path& directory);
		AssetManager(
			const stdf::path& directory,
			LoadingPolicy loading_policy,
			UnloadingPolicy unloading_policy
		);
		
		// getDirectory
		const stdf::path getDirectory() const;

    // lockAsset
    virtual SharedPtr<Asset> lockAsset(
      const AssetKey& key, AssetFactory factory
    ) override;
    // addAsset
    virtual UUID addAsset(SharedPtr<Asset> asset) override;
	private:
		stdf::path _directory;
		LoadingPolicy _loading_policy = LoadingPolicy::LAZY_LOAD;
		UnloadingPolicy _unloading_policy = UnloadingPolicy::UNLOAD_APP;
    AssetRegistry _registry;
    Map<UUID, Variant<SharedPtr<Asset>, WeakPtr<Asset>>> _loaded;
	};
}