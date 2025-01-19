#include "common.hh"
#include "model.hh"
#include "debug/engine_logger.hh"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Parrot {
    // processSubModel (static)
    static SubModel processSubModel(aiMesh* mesh, const aiScene* scene) {
        List<Vertex> vertices;
        List<uint> indices;
        for (uint i = 0; i < mesh->mNumVertices; ++i) {
            Vertex& vertex = vertices.emplace_back();
            // position
            vertex.position = {
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z,
            };
            // normal
            vertex.normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z,
            };
            // tex_coords
            if (mesh->mTextureCoords[0]) {
                vertex.tex_coords = {
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y,
                };
            }
        }
        for(uint i = 0; i < mesh->mNumFaces; ++i) {
            aiFace& face = mesh->mFaces[i];
            for(uint j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }  
        // TODO: MaterialNode
        return { { std::move(vertices), std::move(indices) }, {} };
    }
    // processNode (static)
    static void processNode(aiNode* node, const aiScene* scene, List<SubModel>& submodels) {
        for (uint i = 0; i < node->mNumMeshes; ++i) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            submodels.emplace_back(processSubModel(mesh, scene));			
        }
        for (uint i = 0; i < node->mNumChildren; ++i) {
            processNode(node->mChildren[i], scene, submodels);
        }
    }

    // Model
    Model::Model(const stdf::path& filepath) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filepath.string(), aiProcess_Triangulate);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
            return;
        }
        processNode(scene->mRootNode, scene, submodels);
        LOG_ASSET_DEBUG("loaded model {} with {} submodel(s)", filepath, submodels.size());
    }
}