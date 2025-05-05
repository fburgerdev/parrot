#pragma once
#include "_asset_node.hh"

namespace Parrot {
  template<class T>
  class AssetAdapter : public _AssetNode<>, public T {
  public:
    using _AssetNode<>::_AssetNode;

    virtual bool loadAsset(LoadContext& context) override;
  };
  //template<class T>
  //class SerialAssetAdapter : public _Asset, protected T {
  //public:
  //  virtual bool loadAsset(LoadContext& context) override {
  //    context.deserializer.deserialize(context.asset_path.file, *this);
  //    return true;
  //  }
  //  StructureNode structure();
  //};
}