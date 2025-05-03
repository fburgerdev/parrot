#pragma once
#include "_asset_node.hh"

namespace Parrot {
  template<class T>
  class AssetAdapter : public _Asset, protected T {
    virtual bool loadAsset(LoadContext& context) override;
  };
  template<class T>
  class SerialAssetAdapter : public _Asset, protected T {
  public:
    virtual bool loadAsset(LoadContext& context) override {
      context.deserializer.deserialize(context.asset_path.file, *this);
      return true;
    }
    StructureNode structure();
  };
  template<AssetHandleType Handle, class Node>
    requires AssetNodeType<Node, Handle>
  Opt<Handle> fromSerialNode(const SerialNode& node, const SerialPath& path, Node& parent) {
    using Type = typename Handle::Type;
    if (node.isInt() && node.isUint()) {
      return parent.createAssetHandle<Type>(node.value<UUID>());
    }
    else if (node.isString()) {
      AssetPath asset_path{ stdf::path{node.value<string>()} };
      return parent.createAssetHandle<Type>(asset_path);
    }
    else if (node.isMap()) {
      AssetPath asset_path{ path.file, path.sub };
      return parent.createAssetHandle<Type>(asset_path);
    }
    return std::nullopt;
  }
}