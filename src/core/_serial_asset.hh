#pragma once
#include "_asset.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  class _SerialAsset : public _Asset {
    virtual bool loadAsset(const AssetPath& path) override {
      return true;
      //return loadAsset(SerialNode::loadFromJSON(path.file));
    }
    //virtual bool loadAsset(const SerialNode& node) = 0;
  };
}