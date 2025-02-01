#pragma once
#include "client.hh"

namespace Parrot {
  // WaterMesh
  class WaterMesh : public EntityScript {
  public:
    // (constructor)
    WaterMesh(Entity& entity, AssetAPI& asset_api)
      : EntityScript(entity, asset_api) {}

    // onAttach
    virtual void onAttach() override {

    }
  };
}