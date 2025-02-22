#pragma once
#include "asset_path.hh"
#include "utils/uuid.hh"

namespace Parrot {
  // Asset
  class Asset : public UUIDObject {
  public:
    // (constructor)
    Asset() = default;
    Asset(const AssetPath& asset_path);
    Asset(AssetPath&& asset_path);

    // asset_path
    AssetPath asset_path;
  };
  // AssetType
  template<class T>
  concept AssetType = std::is_base_of_v<Asset, T>;
}