#pragma once
#include "asset_path.hh"
#include "utils/uuid.hh"

namespace Parrot {
  /// @brief Base class for game assets. 
  class Asset : public UUIDObject {
  public:
    /// @brief Construct empty Asset with no data
    Asset() = default;
    /// @param path Path the Asset is loaded from
    Asset(const AssetPath& path);
    /// @param path Path the Asset is loaded from
    Asset(AssetPath&& path);

    /// @return The AssetPath where this Asset is loaded from
    const AssetPath& getAssetPath() const;
  private:
    AssetPath _path;
  };
}