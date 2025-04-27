#pragma once
#include "core/asset_path.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  class _IAssetManager;
  class _Asset {
  public:
    _Asset(_IAssetManager* manager = nullptr)
      : _manager(manager) {}

    virtual bool loadAsset(const AssetPath& path) = 0;
    friend class _AssetNode;
    template<class T>
    friend class _AssetHandle;
  private:
    _IAssetManager* _manager;
  };
  class _SerialAsset : public _Asset {
    virtual bool loadAsset(const AssetPath& path) override {
      return loadAsset(SerialNode::loadFromJSON(path.file));
    }
    virtual bool loadAsset(const SerialNode& node) = 0;
  };
}