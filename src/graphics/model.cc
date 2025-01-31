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
    return {
      { std::move(vertices), std::move(indices) },
      mesh->mMaterialIndex
    };
  }
  // processNode (static)
  static void processNode(
    aiNode* node, const aiScene* scene, List<SubModel>& submodels
  ) {
    for (uint i = 0; i < node->mNumMeshes; ++i) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      submodels.emplace_back(processSubModel(mesh, scene));      
    }
    for (uint i = 0; i < node->mNumChildren; ++i) {
      processNode(node->mChildren[i], scene, submodels);
    }
  }

  // (constructor)
  Model::Model(const AssetPath& asset_path, AssetAPI& asset_api)
    : Asset(asset_path) {
    Assimp::Importer importer;
    uint flags = 0;
    flags |= aiProcess_Triangulate;
    flags |= aiProcess_FlipUVs;
    flags |= aiProcess_FlipWindingOrder;
    const aiScene* scene = importer.ReadFile(asset_path.filepath.string(), flags);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    processNode(scene->mRootNode, scene, submodels);
    for (uint i = 0; i < scene->mNumMaterials; ++i) {
      auto& model_material = model_materials.emplace_back();
      auto& material = *scene->mMaterials[i];
      // diffuse
      uint diffuse_count = material.GetTextureCount(aiTextureType_DIFFUSE);
      for (uint j = 0; j < diffuse_count; ++j) {
        aiString name;
        material.GetTexture(aiTextureType_DIFFUSE, j, &name);
        const auto* texture = scene->GetEmbeddedTexture(name.C_Str());
        if (texture->mHeight == 0) {
          model_material.tex_index = textures.size();
          UUID uuid = asset_api.addAsset(std::make_shared<Image>(
            name.C_Str(), (const uchar*)texture->pcData, texture->mWidth
          ));
          textures.emplace_back(AssetHandle<Image>(uuid, asset_api));
        }
      }
    }
    LOG_ASSET_DEBUG("loaded model {} with {} submodel(s) and {}", asset_path.filepath, submodels.size(), textures.size());
  }
}