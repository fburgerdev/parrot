#pragma once
#include "core/asset_handle.hh"

namespace Parrot {
  class AssetRegistry {
  public:
    AssetRegistry() = default;
    AssetRegistry(const stdf::path& asset_dir);

    UUID getUUID(const AssetPath& asset_path) const;
    UUID getUUID(const AssetKey& key) const;
    const AssetPath& getAssetPath(UUID uuid) const;
    const AssetPath& getAssetPath(const AssetKey& key) const;

    bool contains(UUID uuid) const;
    bool contains(const AssetPath& asset_path) const;
    const AssetPath* find(UUID uuid) const;
    UUID find(const AssetPath& asset_path) const;
    void add(UUID uuid, const AssetPath& asset_path);
    void add(const stdf::path& path);
    void add(const AssetPath& asset_path);
    void remove(UUID uuid);
    void remove(const AssetPath& asset_path);
  private:
    stdf::path _asset_dir;
    Map<UUID, AssetPath> _asset_path_map;
    Map<AssetPath, UUID> _uuid_map;
  };
}