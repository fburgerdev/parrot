#pragma once
#include "asset_path.hh"
#include "utils/uuid.hh"

namespace Parrot {
  /// @ingroup Internals
  /// @brief Base class for game assets. 
  class Asset : public UUIDObject {
  public:
    /// @trivial
    Asset() = default;
    /// @trivial
    Asset(const AssetPath& path);
    /// @trivial
    Asset(AssetPath&& path);

    /// @trivial
    const AssetPath& getAssetPath() const;
  private:
    AssetPath _path;
  };
  /// @ingroup Internals
  /// @brief Requirements for game assets.
  template<class T>
  concept AssetType = requires(T asset, ostream&& source) {
    T(std::move(source));
  } && std::is_base_of_v<Asset, T>;
}