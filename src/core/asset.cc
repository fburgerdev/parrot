#include "common.hh"
#include "asset.hh"

namespace Parrot {
  // (constructor)
  Asset::Asset(const AssetPath& path)
    : _path(path) {}
  Asset::Asset(AssetPath&& path)
    : _path(std::move(path)) {}
  
  // getAssetPath
  const AssetPath& Asset::getAssetPath() const {
    return _path;
  }
}