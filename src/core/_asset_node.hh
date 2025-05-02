#pragma once
#include "_asset_handle.hh"

namespace Parrot {
  template<class T = _Asset>// requires std::is_base_of_v<_Asset, T>
  class _AssetNode : public T {
  public:
    _AssetNode(_AssetManager& manager)
      : _manager(&manager) {}

    template<class U>
    _AssetHandle<U> createAssetHandle(const AssetKey& key) {
      return { _manager->registerAsset(key, *this), *_manager };
    }
  private:
    _AssetManager* _manager = nullptr;
  };

  template<class T, class Handle>
  concept AssetNodeType = requires(T x, AssetKey key) {
    { x.createAssetHandle<typename Handle::Type>(key) } -> std::same_as<Handle>;
  };
}