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
      static constexpr uint RESOLUTION = 5;
      static constexpr float32 WATER_DEPTH = 10.0F, ISLAND_HEIGHT = 10.0F;
      // heights
      auto rng = RNG<>(0);
      List<float32> heights = generatePerlin2D<float32>(
        { WIDTH * RESOLUTION, DEPTH * RESOLUTION }, { 2, 2 }, 4, rng
      );
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
      for (uint z = 0; z < DEPTH * RESOLUTION; ++z) {
        for (uint x = 0; x < WIDTH * RESOLUTION; ++x) {
          mesh.vertices.push_back({
            .position = {
              float32(x) / RESOLUTION - float32(WIDTH) / 2,
              heights[WIDTH * RESOLUTION * z + x],
              float32(z) / RESOLUTION - float32(DEPTH) / 2,
            },
            .tex_coords = {
              float32(x) / (WIDTH * RESOLUTION),
              float32(z) / (DEPTH * RESOLUTION)
            },
          });
        }
      }
      for (uint z = 0; z < DEPTH * RESOLUTION - 1; ++z) {
        for (uint x = 0; x < WIDTH * RESOLUTION - 1; ++x) {
          mesh.indices.push_back(WIDTH * RESOLUTION * (z + 0) + (x + 0));
          mesh.indices.push_back(WIDTH * RESOLUTION * (z + 0) + (x + 1));
          mesh.indices.push_back(WIDTH * RESOLUTION * (z + 1) + (x + 1));
          mesh.indices.push_back(WIDTH * RESOLUTION * (z + 0) + (x + 0));
          mesh.indices.push_back(WIDTH * RESOLUTION * (z + 1) + (x + 1));
          mesh.indices.push_back(WIDTH * RESOLUTION * (z + 1) + (x + 0));
        }
      }
      calcGridNormals(WIDTH * RESOLUTION, DEPTH * RESOLUTION, mesh.vertices);
      // asset
      _asset = std::make_shared<Model>("terrain");
      _asset->submodels.emplace_back(
        mesh, 0
      );
      _handle = AssetHandle<Model>(asset_api->addAsset(_asset), *asset_api);
      entity->getComponent<RenderObjectComponent>().model = _handle;

      // border
      auto children = entity->findByTag("Border");
      auto& child = **children.begin();
      Mesh border_mesh;
      for (uint z : List<uint>({ 0, DEPTH * RESOLUTION - 1 })) {
        for (uint x = 0; x < WIDTH * RESOLUTION; ++x) {
          border_mesh.vertices.push_back({
            .position = {
              float32(x) / RESOLUTION - float32(WIDTH) / 2,
              -10,
              float32(z) / RESOLUTION - float32(DEPTH) / 2,
            },
            .normal = { 0, 0, -1 },
            .tex_coords = {
              float32(z) / (WIDTH * RESOLUTION),
              float32(z) / (DEPTH * RESOLUTION)
            },
          });
        }
        for (uint x = 0; x < WIDTH * RESOLUTION; ++x) {
          border_mesh.vertices.push_back({
            .position = {
              float32(x) / RESOLUTION - float32(WIDTH) / 2,
              heights[WIDTH * RESOLUTION * z + x],
              float32(z) / RESOLUTION - float32(DEPTH) / 2,
            },
            .normal = mesh.vertices.at(WIDTH * RESOLUTION * z + x).normal,
            .tex_coords = {
              float32(x) / (WIDTH * RESOLUTION),
              float32(z) / (DEPTH * RESOLUTION)
            },
          });
        }
      }
      for (uint x = 0; x < WIDTH * RESOLUTION - 1; ++x) {
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (0 + 0) + (x + 0));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (0 + 0) + (x + 1));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (0 + 1) + (x + 1));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (0 + 0) + (x + 0));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (0 + 1) + (x + 1));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (0 + 1) + (x + 0));
      }
      for (uint x = 0; x < WIDTH * RESOLUTION - 1; ++x) {
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (2 + 0) + (x + 0));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (2 + 1) + (x + 1));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (2 + 0) + (x + 1));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (2 + 0) + (x + 0));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (2 + 1) + (x + 0));
        border_mesh.indices.push_back(WIDTH * RESOLUTION * (2 + 1) + (x + 1));
      }

      usize offset = border_mesh.vertices.size();
      for (uint x : List<uint>({ 0, WIDTH * RESOLUTION - 1 })) {
        for (uint z = 0; z < DEPTH * RESOLUTION; ++z) {
          border_mesh.vertices.push_back({
            .position = {
              float32(x) / RESOLUTION - float32(WIDTH) / 2,
              -10,
              float32(z) / RESOLUTION - float32(DEPTH) / 2,
            },
            .normal = { 0, 0, -1 },
            .tex_coords = {
              float32(z) / (WIDTH * RESOLUTION),
              float32(z) / (DEPTH * RESOLUTION)
            },
            });
        }
        for (uint z = 0; z < DEPTH * RESOLUTION; ++z) {
          border_mesh.vertices.push_back({
            .position = {
              float32(x) / RESOLUTION - float32(WIDTH) / 2,
              heights[WIDTH * RESOLUTION * z + x],
              float32(z) / RESOLUTION - float32(DEPTH) / 2,
            },
            .normal = mesh.vertices.at(WIDTH * RESOLUTION * z + x).normal,
            .tex_coords = {
              float32(x) / (WIDTH * RESOLUTION),
              float32(z) / (DEPTH * RESOLUTION)
            },
            });
        }
      }
      for (uint z = 0; z < DEPTH * RESOLUTION - 1; ++z) {
        border_mesh.indices.push_back(offset + WIDTH * RESOLUTION * (0 + 0) + (z + 0));
        border_mesh.indices.push_back(offset + WIDTH * RESOLUTION * (0 + 1) + (z + 1));
        border_mesh.indices.push_back(offset + WIDTH * RESOLUTION * (0 + 0) + (z + 1));
        border_mesh.indices.push_back(offset + WIDTH * RESOLUTION * (0 + 0) + (z + 0));
        border_mesh.indices.push_back(offset + WIDTH * RESOLUTION * (0 + 1) + (z + 0));
        border_mesh.indices.push_back(offset + WIDTH * RESOLUTION * (0 + 1) + (z + 1));
      }
      for (uint z = 0; z < DEPTH * RESOLUTION - 1; ++z) {
        border_mesh.indices.push_back(offset + DEPTH * RESOLUTION * (2 + 0) + (z + 0));
        border_mesh.indices.push_back(offset + DEPTH * RESOLUTION * (2 + 0) + (z + 1));
        border_mesh.indices.push_back(offset + DEPTH * RESOLUTION * (2 + 1) + (z + 1));
        border_mesh.indices.push_back(offset + DEPTH * RESOLUTION * (2 + 0) + (z + 0));
        border_mesh.indices.push_back(offset + DEPTH * RESOLUTION * (2 + 1) + (z + 1));
        border_mesh.indices.push_back(offset + DEPTH * RESOLUTION * (2 + 1) + (z + 0));
      }
      // asset
      _border_asset = std::make_shared<Model>("border");
      _border_asset->submodels.emplace_back(
        std::move(border_mesh), 0
      );
      _border_handle = AssetHandle<Model>(asset_api->addAsset(_border_asset), *asset_api);
      child.getComponent<RenderObjectComponent>().model = _border_handle;
    }
  private:
    AssetHandle<Model> _handle;
    AssetHandle<Model> _border_handle;
    SharedPtr<Model> _asset;
    SharedPtr<Model> _border_asset;
  };
}