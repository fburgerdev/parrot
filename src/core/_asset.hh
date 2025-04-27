#pragma once
#include "core/asset_path.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  class _AssetManager;
  class _Asset {
  public:
    virtual bool loadAsset(const AssetPath& path) = 0;

    template<class T>
    friend class _AssetNode;
    template<class T>
    friend class _AssetHandle;
  protected:
    _Asset(_AssetManager* manager = nullptr)
      : _manager(manager) {
    }
  private:
    _AssetManager* _manager;
  };
  using AssetRef = SharedPtr<_Asset>;
}