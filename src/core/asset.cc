#include "common.hh"
#include "asset.hh"

namespace Parrot {
  // (constructor)
  Asset::Asset(const AssetPath& asset_path)
    : asset_path(asset_path) {}
  Asset::Asset(AssetPath&& asset_path)
    : asset_path(std::move(asset_path)) {}
}