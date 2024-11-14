#include "common.hh"
#include "manager.hh"

namespace Parrot {
	// AssetManager
	AssetManager::AssetManager(const stdf::path& asset_dir)
		: _asset_dir(stdf::canonical(asset_dir)) {}
}