#pragma once
#include "client.hh"

namespace Parrot {
  // Rotate
  class Rotate : public EntityScript {
  public:
    // (constructor)
    Rotate(Entity& entity, AssetAPI& asset_api)
      : EntityScript(entity, asset_api) {}

    // onUpdate
    virtual void onUpdate(float32 delta_time) override {
      entity->transform.rotation.y += 0.5F * delta_time;
    }
  };
}