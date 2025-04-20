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

  template<class T>
  concept InternalAsset = requires(T asset, SerialNode node) {
    static_cast<Asset>(asset);
    T{AssetPath()};
  };
  template<class T>
  concept ExternalAsset = requires(T asset, stdf::path path) {
    static_cast<Asset>(asset);
    T{path};
  };
  template<class T>
  concept AssetType = InternalAsset<T> || ExternalAsset<T>;
}