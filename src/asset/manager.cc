#include "common.hh"
#include "manager.hh"

namespace Parrot {
	// AssetManager
	AssetManager::AssetManager(const stdf::path& asset_dir)
		: _asset_dir(stdf::canonical(asset_dir)) {}
	AssetManager::AssetManager(
		const stdf::path& asset_dir,
		LoadingPolicy loading_policy,
		UnloadingPolicy unloading_policy)
		: _asset_dir(asset_dir),
		  _loading_policy(loading_policy),
		  _unloading_policy(unloading_policy) {
		// TODO: assert loading_policy <= unloading_policy
	}
}