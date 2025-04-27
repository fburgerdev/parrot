#pragma once
#include "_asset.hh"

namespace Parrot {
  class _AssetManager {
  private:
    virtual AssetRef lockAsset(const AssetKey& key, const Factory<_Asset>& factory) = 0;
    virtual UUID registerAsset(const AssetKey& key, _Asset& parent) = 0;

    friend class _Asset;
    template<class T>
    friend class _AssetNode;
    template<class T>
    friend class _AssetHandle;
  };
}