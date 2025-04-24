#pragma once
#include "mesh.hh"
#include "material.hh"

namespace Parrot {
  struct ModelMaterial {
    usize tex_index = 0xFFFFFF;
  };
  /// @brief Pair of Mesh and index to associated ModelMaterial.
  using SubModel = Pair<Mesh, usize>;
  /// @brief Graphics model consisting of (multiple) Meshes and Materials.
  class Model : public Asset {
  public:
    /// @trivial
    Model(strview name);
    Model(const AssetPath& path, AssetAPI& api);
    Model(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    List<SubModel> submodels;
    /// @warning The order of the elements is important since they are being
    /// referenced by their index in @c submodels
    List<ModelMaterial> model_materials;
    List<TextureConfig> textures;
  };
}