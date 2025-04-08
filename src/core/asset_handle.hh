#pragma once
#include "asset.hh"
#include "asset_path.hh"

namespace Parrot {
  /// @brief Function that loads an Asset from the given location.
  using AssetFactory = Func<SharedPtr<Asset>(const AssetPath&)>;
  /// @brief Interface for an Asset memory manager (loading and unloading).
  class AssetAPI {
  public:
    /// @brief Share ownership to the memory manager.
    /// @warning How long the Asset memory manager holds ownership to that asset
    /// is implementation specific.
    virtual UUID addAsset(SharedPtr<Asset> asset) = 0;
    /// @brief Load an Asset into memory
    /// @param key Identifies the Asset
    /// @param factory Used to construct the Asset
    /// @return A reference to the loaded Asset
    virtual SharedPtr<const Asset> lockAsset(
      const AssetKey& key, AssetFactory factory
    ) = 0;
  };
  /// @brief Reference to an Asset that doesn't require the Asset to be loaded.
  template<class T>
  class AssetHandle {
  public:
    /// @brief Construct empty AssetHandle.
    AssetHandle() = default;
    /// @param uuid The UUID of the handled Asset
    /// @param api Used to @c lock the Asset 
    AssetHandle(UUID uuid, AssetAPI& api);
    /// @param uuid The AssetPath of the handled Asset
    /// @param api Used to @c lock the Asset 
    AssetHandle(const AssetPath& path, AssetAPI& api);
    /// @param uuid The AssetKey of the handled Asset
    /// @param api Used to @c lock the Asset 
    AssetHandle(const AssetKey& key, AssetAPI& api);
    /// @deprecated
    AssetHandle(const SerialNode& node, AssetAPI& api);

    /// @return Whether the AssetHandle is non-empty
    operator bool() const;
    /// @brief Load Asset into memory if necessary and return a reference.
    /// @return A reference to the Asset
    /// @note For efficient memory usage,
    /// hold this SharedPtr only as long as necessary.
    SharedPtr<const T> lock() const;
  private:
    AssetKey _key = UUID(0);
    AssetAPI* _api = nullptr;
  };
}
#define ASSET_HANDLE_HH
#include "asset_handle_impl.hh"