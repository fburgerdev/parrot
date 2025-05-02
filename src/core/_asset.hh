#pragma once
#include "core/asset_path.hh"
#include "utils/deserializer.hh"

namespace Parrot {
  class _AssetManager;
  class _Asset {
  public:
    struct LoadContext {
      AssetPath asset_path;
      istream& data_stream;
      Deserializer& deserializer;
    };

    virtual bool loadAsset(LoadContext& context) = 0;
  };
  using AssetRef = SharedPtr<_Asset>;
}