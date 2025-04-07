#include "common.hh"
#include "material.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  //* MaterialNode
  // (constructor)
  MaterialNode::MaterialNode(const SerialNode& node, AssetAPI& api) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void MaterialNode::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    // object
    if (node.isMap()) {
      Map<string, MaterialNode> map;
      for (const auto& [key, value] : node.items()) {
        map.try_emplace(key, value, api);
      }
      value = std::move(map);
    }
    // list or leaf
    else if (node.isList()) {
      const auto& array = node;
      // leaf
      if (array.size() == 2 && array.at(0).isString()) {
        string dtype = normalized(string(array.at(0)));
        // i32
        if (dtype == "i32") {
          value = MaterialLeaf(int32(array.at(1)));
        }
        else if (dtype == "vec2i32") {
          value = MaterialLeaf(parseVec<int32, 2>(array.at(1)));
        }
        else if (dtype == "vec3i32") {
          value = MaterialLeaf(parseVec<int32, 3>(array.at(1)));
        }
        else if (dtype == "vec4i32") {
          value = MaterialLeaf(parseVec<int32, 4>(array.at(1)));
        }
        // f32
        if (dtype == "f32") {
          value = MaterialLeaf(float32(array.at(1)));
        }
        else if (dtype == "vec2f32") {
          value = MaterialLeaf(parseVec<float32, 2>(array.at(1)));
        }
        else if (dtype == "vec3f32") {
          value = MaterialLeaf(parseVec<float32, 3>(array.at(1)));
        }
        else if (dtype == "vec4f32") {
          value = MaterialLeaf(parseVec<float32, 4>(array.at(1)));
        }
        else if (dtype == "mat2f32") {
          value = MaterialLeaf(parseMat<float32, 2>(array.at(1)));
        }
        else if (dtype == "mat3f32") {
          value = MaterialLeaf(parseMat<float32, 3>(array.at(1)));
        }
        else if (dtype == "mat4f32") {
          value = MaterialLeaf(parseMat<float32, 4>(array.at(1)));
        }
        // f64
        if (dtype == "f64") {
          value = MaterialLeaf(float64(array.at(1)));
        }
        else if (dtype == "vec2f64") {
          value = MaterialLeaf(parseVec<float64, 2>(array.at(1)));
        }
        else if (dtype == "vec3f64") {
          value = MaterialLeaf(parseVec<float64, 3>(array.at(1)));
        }
        else if (dtype == "vec4f64") {
          value = MaterialLeaf(parseVec<float64, 4>(array.at(1)));
        }
        else if (dtype == "mat2f64") {
          value = MaterialLeaf(parseMat<float64, 2>(array.at(1)));
        }
        else if (dtype == "mat3f64") {
          value = MaterialLeaf(parseMat<float64, 3>(array.at(1)));
        }
        else if (dtype == "mat4f64") {
          value = MaterialLeaf(parseMat<float64, 4>(array.at(1)));
        }
        // texture
        else if (dtype == "texture") {
          value = MaterialLeaf(
            AssetHandle<TextureConfig>(array.at(1), api)
          );
        }
        // frame
        else if (dtype == "frame") {
          value = MaterialLeaf(FrameName(array.at(1)));
        }
      }
      // list
      else {
        List<MaterialNode> list;
        for (const auto& el : array) {
          list.emplace_back(el, api);
        }
        value = std::move(list);
      }
    }
  }
  
  // normalized
  string MaterialNode::normalized(const string& str) {
    string out;
    for (char ch : str) {
      out.push_back(std::tolower(ch));
    }
    return out;
  }

  //* Material
  // (constructor) for Asset
  Material::Material(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  Material::Material(
    const SerialNode& node, const AssetPath& path, AssetAPI& api
  ) : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void Material::loadFromSerialNode(
    const SerialNode& node, AssetAPI& api
  ) {
    // root
    if (node.contains("uniforms")) {
      root.loadFromSerialNode(node.at("uniforms"), api);
    }
    // shader
    if (node.contains("shader")) {
      shader = AssetHandle<ShaderProgram>(node.at("shader"), api);
    }
    else {
      shader = AssetHandle<ShaderProgram>(
        AssetPath(stdf::path(string(".parrot/model.program.json"))), api
      );
    }
  }
}