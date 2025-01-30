#pragma once
#include "core/asset_handle.hh"

namespace Parrot {
  // AssetRegistry
  class AssetRegistry {
  public:
    // (constructor)
    AssetRegistry() = default;
    AssetRegistry(const stdf::path& asset_directory);

    // getUUID
    UUID getUUID(const AssetPath& asset_path) const;
    UUID getUUID(const AssetKey& key) const;
    // getAssetPath
    const AssetPath& getAssetPath(UUID uuid) const;
    const AssetPath& getAssetPath(const AssetKey& key) const;

    // contains
    bool contains(UUID uuid) const;
    bool contains(const AssetPath& asset_path) const;
    // find
    const AssetPath* find(UUID uuid) const;
    UUID find(const AssetPath& asset_path) const;
    // add
    void add(UUID uuid, const AssetPath& asset_path);
    void add(const stdf::path& path);
    void add(const AssetPath& asset_path);
    // remove
    void remove(UUID uuid);
    void remove(const AssetPath& asset_path);
  private:
    stdf::path _asset_directory;
    Map<UUID, AssetPath> _asset_path_map;
    Map<AssetPath, UUID> _uuid_map;
  };
}