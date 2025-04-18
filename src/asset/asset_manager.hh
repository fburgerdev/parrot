#pragma once
#include "core/asset_handle.hh"
#include "asset_policy.hh"

namespace Parrot {
  /// @brief Load and release Assets from memory and return references.
  class AssetManager : public AssetAPI {
  public:
    AssetManager() = default;
    AssetManager(const stdf::path& asset_dir);
    AssetManager(const stdf::path& asset_dir,
      LoadingPolicy load, UnloadingPolicy unload
    );
    
    /// @trivial 
    const stdf::path& getAssetDirectory() const;

    /// @brief Share ownership of an Asset with the AssetManager.
    /// @return The UUID of the shared Asset
    virtual UUID addAsset(SharedPtr<Asset> asset) override;
    /// @brief Get an Asset instance based on an AssetKey.
    virtual SharedPtr<const Asset> lockAsset(
      const AssetKey& key, AssetFactory factory
    ) override;
  private:
    class Registry {
    public:
      Registry() = default;
      Registry(const stdf::path& asset_dir);

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

    stdf::path _asset_dir;
    LoadingPolicy _load_policy = LoadingPolicy::LAZY_LOAD;
    UnloadingPolicy _unload_policy = UnloadingPolicy::UNLOAD_APP;
    Registry _registry;
    Map<UUID, Variant<SharedPtr<Asset>, WeakPtr<Asset>>> _loaded;
  };
}