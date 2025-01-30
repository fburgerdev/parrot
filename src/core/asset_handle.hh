#pragma once
#include "asset.hh"
#include "asset_path.hh"

namespace Parrot {
  // AssetKey
  using AssetKey = Variant<UUID, AssetPath>;
  class AssetLocker {
  public:
    virtual SharedPtr<Asset> lock(const AssetKey& key, Func<SharedPtr<Asset>(const AssetPath&)> func) = 0;
    virtual void add(UUID uuid, const AssetPath& asset_path, SharedPtr<Asset>) = 0;
  };
  // AssetResolver
  using AssetResolver = Func<SharedPtr<Asset>(const AssetKey&)>;
  // AssetHandle
  template<class T> // requires std::is_base_of_v<T, Asset>
  class AssetHandle {
  public:
    // (constructor)
    AssetHandle() = default;
    AssetHandle(UUID uuid, AssetLocker& locker)
      : _key(uuid), _locker(&locker) {}
    AssetHandle(const AssetPath& path, AssetLocker& locker)
      : _key(path), _locker(&locker) {}
    AssetHandle(const AssetKey& key, AssetLocker& locker)
      : _key(key), _locker(&locker) {}
    template<JsonType JSON>
    AssetHandle(const JSON& json, AssetLocker& locker)
      : _locker(&locker) {
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
    AssetLocker* _locker = nullptr;
  };
}