#pragma once
#include "_asset_handle.hh"

namespace Parrot {
  template<class T = _Asset>// requires std::is_base_of_v<_Asset, T>
  class _AssetNode : public T {
  public:
    template<class U>
    _AssetHandle<U> createAssetHandle(const AssetKey& key) {
      return { this->_manager->registerAsset(key, *this), *this->_manager };
    }

    template<class T>
    friend class _AssetHandle;
  private:
    using T::T;
  };

  template<class T, class Handle>
  concept AssetNodeType = requires(T x, AssetKey key) {
    { x.createAssetHandle<typename Handle::Type>(key) } -> std::same_as<Handle>;
  };
}