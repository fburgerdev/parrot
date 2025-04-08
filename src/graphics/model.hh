#pragma once
#include "mesh.hh"
#include "material.hh"

namespace Parrot {
  struct ModelMaterial {
    usize tex_index = 0xFFFFFF;
  };
  using SubModel = Pair<Mesh, usize>;
  class Model : public Asset {
  public:
    Model(strview name);
    Model(const AssetPath& path, AssetAPI& api);
    Model(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    List<SubModel> submodels;
    List<ModelMaterial> model_materials;
    List<TextureConfig> textures;
  };
}