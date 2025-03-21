#pragma once
#include "asset_path.hh"
#include "utils/uuid.hh"

namespace Parrot {
  // Asset
  class Asset : public UUIDObject {
  public:
    // (constructor)
    Asset() = default;
    Asset(const AssetPath& path);
    Asset(AssetPath&& path);

    // getAssetPath
    const AssetPath& getAssetPath() const;
  private:
    AssetPath _path;
  };
  // AssetType
  template<class T>
  concept AssetType = std::is_base_of_v<Asset, T>;
}