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
    MaterialNode(const SerialNode& node, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // value
    Variant<
      Map<string, MaterialNode>, List<MaterialNode>, MaterialLeaf
    > value;
  private:
    static string normalized(const string& str);
    template<class T, usize N>
    static Vec<T, N> parseVec(const auto& node);
    template<class T, usize N, usize M = N>
    static Mat<T, N, M> parseMat(const auto& node);
  };

  // Material (Asset)
  class Material : public Asset {
  public:
    // (constructor) for Asset
    Material(const AssetPath& path, AssetAPI& api);
    Material(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // root, shader
    MaterialNode root;
    AssetHandle<ShaderProgram> shader;
  };
}
#include "material_impl.hh"