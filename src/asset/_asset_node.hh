#pragma once
#include "_asset_handle.hh"

namespace Parrot {
  class _AssetNode : public _Asset {
  public:
    template<class T>
    _AssetHandle<T> createAssetHandle(const AssetKey& key) {
      return { _manager->addAsset(key, *this), *_manager };
    }

    template<class T>
    friend class _AssetHandle;
  private:
    using _Asset::_Asset;
  };
}