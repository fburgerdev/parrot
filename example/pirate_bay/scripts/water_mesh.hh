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
      Mesh mesh;
      for (int x = -50; x < 50; ++x) {
        for (int z = -50; z < 50; ++z) {
          Vertex v1 = { .position = { float32(x + 0), 0, float32(z + 0)} };
          Vertex v2 = { .position = { float32(x + 1), 0, float32(z + 0)} };
          Vertex v3 = { .position = { float32(x + 0), 0, float32(z + 1)} };
          Vertex v4 = { .position = { float32(x + 1), 0, float32(z + 1)} };
          mesh.addQuadrangle(v1, v2, v3, v4);
        }
      }
      _asset = std::make_shared<Model>("water_model");
      _asset->submodels.emplace_back(
        std::move(mesh), 0
      );
      _handle = AssetHandle<Model>(asset_api->addAsset(_asset), *asset_api);
      entity->getComponent<RenderObjectComponent>().model = _handle;
    }
  private:
    AssetHandle<Model> _handle;
    SharedPtr<Model> _asset;
  };
}