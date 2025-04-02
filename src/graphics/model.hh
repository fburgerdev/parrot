#pragma once
#include "mesh.hh"
#include "material.hh"

namespace Parrot {
  // ModelMaterial
  struct ModelMaterial {
    usize tex_index = 0xFFFFFF;
  };
  // SubModel
  using SubModel = Pair<Mesh, usize>;
  // Model (Asset)
  class Model : public Asset {
  public:
    // (constructor)
    Model(strview name);
    // :: for Asset
    Model(const AssetPath& path, AssetAPI& api);
    Model(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {}

    // submodels, model_materials, textures
    List<SubModel> submodels;
    List<ModelMaterial> model_materials;
    List<TextureConfig> textures;
  };
}