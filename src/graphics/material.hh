#pragma once
#include "shader_source.hh"
#include "texture_config.hh"
#include "math/matrix.hh"

namespace Parrot {
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
		// numeric
		NumericMaterialLeaf,
		// texture
		AssetHandle<TextureConfig>
	>;
	// MaterialNode
	struct MaterialNode {
		// (constructor)
		MaterialNode() = default;
		template<JsonType JSON>
		MaterialNode(const JSON& json, AssetAPI& asset_api) {
			loadFromJSON(json, asset_api);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
			// object
			if (json.is_object()) {
				Map<string, MaterialNode> map;
				for (const auto& [key, value] : json.items()) {
					map.try_emplace(key, value, asset_api);
				}
				value = std::move(map);
			}
			// list or leaf
			else if (json.is_array()) {
				const List<JSON>& array = json;
				// leaf
				if (array.size() == 2 && array.at(0).is_string()) {
					string dtype = normalized(array.at(0));
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
							AssetHandle<TextureConfig>(array.at(1), asset_api)
						);
					}
				}
				// list
				else {
					List<MaterialNode> list;
					for (const auto& el : array) {
						list.emplace_back(el, asset_api);
					}
					value = std::move(list);
				}
			}
		}

		// value
		Variant<
			Map<string, MaterialNode>,
			List<MaterialNode>,
			MaterialLeaf
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
		Material(const AssetPath& asset_path, AssetAPI& asset_api);
		template<JsonType JSON>
		Material(
			const JSON& json, const AssetPath& asset_path, AssetAPI& asset_api
		) : Asset(asset_path) {
			loadFromJSON(json, asset_api);
		}

		// loadFromJSON
		template<JsonType JSON>
		void loadFromJSON(const JSON& json, AssetAPI& asset_api) {
			// root
			if (json.contains("uniforms")) {
				root.loadFromJSON(json.at("uniforms"), asset_api);
			}
			// shader
			shader = AssetHandle<ShaderSource>(json.at("shader"), asset_api);
		}

		// root, shader
		MaterialNode root;
		AssetHandle<ShaderSource> shader;
	};
}