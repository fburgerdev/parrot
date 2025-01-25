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
    // Model
    class Model : public UUIDObject {
    public:
        // Model
		Model() = default;
        Model(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Model(const JSON& json, const stdf::path& filepath) {}

        // submodels, model_materials, textures
        List<SubModel> submodels;
        List<ModelMaterial> model_materials;
        List<TextureConfig> textures;
    };
}