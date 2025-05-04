#pragma once
#include "_asset.hh"
#include "core/factory.hh"
#include "utils/deserializer.hh"

namespace Parrot {
  class _AssetManager {
  public:
    virtual AssetRef lockAsset(const AssetKey& key, const Factory<_Asset>& factory) = 0;
    virtual UUID registerAsset(const AssetKey& key, _Asset& parent) = 0;
  };
}