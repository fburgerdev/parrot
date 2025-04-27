#pragma once
#include "_asset_handle.hh"

namespace Parrot {
  template<class T = _Asset>// requires std::is_base_of_v<_Asset, T>
  class _AssetNode : public T {
  public:
    template<class T>
    _AssetHandle<T> createAssetHandle(const AssetKey& key) {
      return { this->_manager->registerAsset(key, *this), *this->_manager };
    }

    template<class T>
    friend class _AssetHandle;
  private:
    using T::T;
  };
}