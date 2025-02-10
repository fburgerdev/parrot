#pragma once
#include "client.hh"

namespace Parrot {
  // calcGridNormals
  void calcGridNormals(uint width, uint depth, List<Vertex>& vertices) {
    for (uint z = 0; z < depth; ++z) {
      for (uint x = 0; x < width; ++x) {
        Vec3<> sum = { 0, 0, 0 };
        Vec3<> position = vertices[width * z + x].position;
        if (0 < x) {
          if (0 < z) {
            sum += cross(
              vertices[width * (z + 0) + (x - 1)].position - position,
              vertices[width * (z - 1) + (x + 0)].position - position
            );
          }
          if (z + 1 < depth) {
            sum += cross(
              vertices[width * (z + 1) + (x + 0)].position - position,
              vertices[width * (z + 0) + (x - 1)].position - position
            );
          }
        }
        if (x + 1 < width) {
          if (0 < z) {
            sum += cross(
              vertices[width * (z - 1) + (x + 0)].position - position,
              vertices[width * (z + 0) + (x + 1)].position - position
            );
          }
          if (z + 1 < depth) {
            sum += cross(
              vertices[width * (z + 0) + (x + 1)].position - position,
              vertices[width * (z + 1) + (x + 0)].position - position
            );
          }
        }
        vertices[width * z + x].normal = normalized(sum);
      }
    }
  }

  // TerrainMesh
  class TerrainMesh : public EntityScript {
  public:
    // (constructor)
    TerrainMesh(Entity& entity, AssetAPI& asset_api)
      : EntityScript(entity, asset_api) {}

    // onAttach
    virtual void onAttach() override {
      static constexpr uint WIDTH = 100, DEPTH = 100;
      static constexpr float32 WATER_DEPTH = 10.0F, ISLAND_HEIGHT = 10.0F;
      // heights
      List<float32> heights = generatePerlin2D(WIDTH, DEPTH, 2.3F);
      float32 min_height = +99999, max_height = -99999;
      for (float32 height : heights) {
        min_height = std::min(height, min_height);
        max_height = std::max(height, max_height);
      }
      for (float32& height : heights) {
        // normalize
        height = ((height - min_height) / (max_height - min_height));
        // rescale
        height = height * (ISLAND_HEIGHT + WATER_DEPTH) - WATER_DEPTH;
      }
      // mesh
      Mesh mesh;
      for (uint z = 0; z < DEPTH; ++z) {
        for (uint x = 0; x < WIDTH; ++x) {
          mesh.vertices.push_back({
            .position = {
              x - float32(WIDTH) / 2,
              heights[WIDTH * z + x],
              z - float32(DEPTH) / 2,
            },
            .tex_coords = { float32(x) / WIDTH, float32(z) / DEPTH },
          });
        }
      }
      for (uint z = 0; z < DEPTH - 1; ++z) {
        for (uint x = 0; x < WIDTH - 1; ++x) {
          mesh.indices.push_back(WIDTH * (z + 0) + (x + 0));
          mesh.indices.push_back(WIDTH * (z + 0) + (x + 1));
          mesh.indices.push_back(WIDTH * (z + 1) + (x + 1));
          mesh.indices.push_back(WIDTH * (z + 0) + (x + 0));
          mesh.indices.push_back(WIDTH * (z + 1) + (x + 1));
          mesh.indices.push_back(WIDTH * (z + 1) + (x + 0));
        }
      }
      calcGridNormals(WIDTH, DEPTH, mesh.vertices);
      // asset
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