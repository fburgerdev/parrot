#pragma once
#include "mesh.hh"
#include "material.hh"

namespace Parrot {
    // SubModel
    using SubModel = Pair<Mesh, MaterialNode>;
    // Model
    class Model : public UUIDObject {
    public:
        // Model
		Model() = default;
        Model(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Model(const JSON& json, const stdf::path& filepath) {}

        // submodels
        List<SubModel> submodels;
    };
}