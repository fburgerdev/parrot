#pragma once
#include "shader.hh"
#include "texture.hh"
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
		Handle<Texture>
	>;
	// MaterialNode
	struct MaterialNode {
		// MaterialNode
		MaterialNode() = default;
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		MaterialNode(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			// object
			if (json.is_object()) {
				Map<string, MaterialNode> map;
				for (const auto& [key, value] : json.items()) {
					map.emplace(key, value);
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
						value = MaterialLeaf(parseHandleFromJSON<Texture>(array.at(1)));
					}
				}
				// list
				else {
					List<MaterialNode> list;
					for (const auto& value : array) {
						list.emplace_back(value);
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

	// Material
	class Material : public UUIDObject {
	public:
		// Material
		Material(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Material(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			// root
			if (json.contains("uniforms")) {
				root.loadFromJSON(json.at("uniforms"));
			}
			// shader
			shader = parseHandleFromJSON<ShaderProgram>(json.at("shader"));
		}

		// root, shader
		MaterialNode root;
		Handle<ShaderProgram> shader;
	};
}