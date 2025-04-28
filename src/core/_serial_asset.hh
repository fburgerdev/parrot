#pragma once
#include "_asset_handle.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  class _SerialAsset : public _Asset {
  public:
    virtual bool loadAsset(const AssetPath& path) override {
      auto& deserializer = _manager->getDeserializer();
      deserializer.deserialize(path.file, *this);
      return true;
    }
    virtual StructureNode structure() = 0;
  };
  template<AssetHandleType Handle, class Node>
    requires AssetNodeType<Node, Handle>
  Opt<Handle> fromSerialNode(const SerialNode& node, const SerialPath& path, Node& parent) {
    using Type = typename Handle::Type;
    if (node.isInt() && node.isUint()) {
      return parent.createAssetHandle<Type>(node.value<UUID>());
    }
    else if (node.isString()) {
      AssetPath asset_path{stdf::path{node.value<string>()}};
      return parent.createAssetHandle<Type>(asset_path);
    }
    else if (node.isMap()) {
      AssetPath asset_path{ path.file, path.sub };
      return parent.createAssetHandle<Type>(asset_path);
    }
    return std::nullopt;
  }
}