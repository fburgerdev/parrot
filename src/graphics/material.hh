#pragma once
#include "shader_source.hh"
#include "texture_config.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  // FrameName
  using FrameName = string;
  // NumericMaterialLeaf
  using NumericMaterialLeaf = Variant<
    // int32
    int32, Vec2<int32>, Vec3<int32>, Vec4<int32>,
    // float32
    float32, Vec2<float32>, Vec3<float32>, Vec4<float32>,
    Mat<float32, 2>, Mat<float32, 3>, Mat<float32, 4>,
    // float64
    float64, Vec2<float64>, Vec3<float64>, Vec4<float64>,
    Mat<float64, 2>, Mat<float64, 3>, Mat<float64, 4>
  >;
  // MaterialLeaf
  using MaterialLeaf = Variant<
    NumericMaterialLeaf, AssetHandle<TextureConfig>, FrameName
  >;
  // MaterialNode
  struct MaterialNode {
    // (constructor)
    MaterialNode() = default;
    template<JsonType JSON>
    MaterialNode(const JSON& json, AssetAPI& api) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // object
      if (json.isMap()) {
        Map<string, MaterialNode> map;
        for (const auto& [key, value] : json.items()) {
          map.try_emplace(key, value, api);
        }
        value = std::move(map);
      }
      // list or leaf
      else if (json.isList()) {
        const auto& array = json;
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

    // value
    Variant<
      Map<string, MaterialNode>, List<MaterialNode>, MaterialLeaf
    > value;
  private:
    static string normalized(const string& str) {
      string out;
      for (char ch : str) {
        out.push_back(std::tolower(ch));
      }
      return out;
    }
    template<class T, usize N>
    static Vec<T, N> parseVec(const auto& json) {
      Vec<T, N> vec;
      for (usize n = 0; n < N; ++n) {
        vec.at(n) = T(json.at(n));
      }
      return vec;
    }
    template<class T, usize N, usize M = N>
    static Mat<T, N, M> parseMat(const auto& json) {
      Mat<T, N, M> mat;
      for (usize n = 0; n < N; ++n) {
        for (usize m = 0; m < M; ++m) {
          mat.at(n, m) = T(json.at(n).at(m));
        }
      }
      return mat;
    }
  };

  // Material (Asset)
  class Material : public Asset {
  public:
    // (constructor) for Asset
    Material(const AssetPath& path, AssetAPI& api);
    template<JsonType JSON>
    Material(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, AssetAPI& api) {
      // root
      if (json.contains("uniforms")) {
        root.loadFromJSON(json.at("uniforms"), api);
      }
      // shader
      if (json.contains("shader")) {
        shader = AssetHandle<ShaderProgram>(json.at("shader"), api);
      }
      else {
        shader = AssetHandle<ShaderProgram>(
          AssetPath(stdf::path(string(".parrot/model.program.json"))), api
        );
      }
    }

    // root, shader
    MaterialNode root;
    AssetHandle<ShaderProgram> shader;
  };
}