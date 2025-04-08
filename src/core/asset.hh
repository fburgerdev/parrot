#pragma once
#include "asset_path.hh"
#include "utils/uuid.hh"

namespace Parrot {
  class Asset : public UUIDObject {
  public:
    Asset() = default;
    Asset(const AssetPath& path);
    Asset(AssetPath&& path);

    const AssetPath& getAssetPath() const;
  private:
    AssetPath _path;
  };
}