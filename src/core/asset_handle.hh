#pragma once
#include "asset.hh"
#include "asset_path.hh"

namespace Parrot {
  // AssetKey
  using AssetKey = Variant<UUID, AssetPath>;
  // AssetAPI
  class AssetAPI {
  public:
    // add
    virtual void add(UUID, const AssetPath&, SharedPtr<Asset>) = 0;
    // lock
    virtual SharedPtr<Asset> lock(
      const AssetKey&, Func<SharedPtr<Asset>(const AssetPath&)>
    ) = 0;
  };
  // AssetResolver
  using AssetResolver = Func<SharedPtr<Asset>(const AssetKey&)>;
  // AssetHandle
  template<class T> // requires std::is_base_of_v<T, Asset>
  class AssetHandle {
  public:
    // (constructor)
    AssetHandle() = default;
    AssetHandle(UUID uuid, AssetAPI& asset_api)
      : _key(uuid), _locker(&asset_api) {}
    AssetHandle(const AssetPath& path, AssetAPI& asset_api)
      : _key(path), _locker(&asset_api) {}
    AssetHandle(const AssetKey& key, AssetAPI& asset_api)
      : _key(key), _locker(&asset_api) {}
    template<JsonType JSON>
    AssetHandle(const JSON& json, AssetAPI& asset_api)
      : _locker(&asset_api) {
      if (json.is_number()) {
        _key = UUID(json);
      }
      else if (json.is_string()) {
        _key = AssetPath(strview(string(json)));
      }
      else {
        UUID uuid = generateUUID();
        _key = uuid;
        std::cout << uuid << std::endl;
        std::cout << json << std::endl;
        _locker->add(uuid, stdf::path(std::to_string(uuid)), 
        std::make_shared<T>(json, stdf::path(std::to_string(uuid)), *_locker));
      }
    }
    
    // lock
    SharedPtr<T> lock() const {
      return std::static_pointer_cast<T>(_locker->lock(_key, [&](const  AssetPath& path) {
        return std::static_pointer_cast<Asset>(std::make_shared<T>(path, *_locker));
      }));
    }
  private:
    AssetKey _key;
    AssetAPI* _locker = nullptr;
  };
}