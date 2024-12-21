#pragma once
#include "graphics/scene_data.hh"
#include "std140_opengl.hh"

namespace Parrot {
	// MAX_LIGHT_COUNT
	constexpr uint MAX_LIGHT_COUNT = 50; // needs to match with shader snippet!
	// (global) block3d_snippet
	inline std::string g_block3d_snippet = R""""(
// light
const uint MAX_LIGHT_COUNT = uint(50); 
// :: ambient
struct AmbientLight {
    float intensity;
    vec3 color;
};
// :: directional
struct DirectionalLight {
    vec3 direction;
    float intensity;
    vec3 color;
};

// block 3d
layout (std140) uniform u_block_3d {
    // world_to_clip
    mat4 u_world_to_clip;

    // light
    // :: ambient
    uint u_ambient_count;
    AmbientLight u_ambient_lights[MAX_LIGHT_COUNT];
    // :: directional
    uint u_directional_count;
    DirectionalLight u_directional_lights[MAX_LIGHT_COUNT];
};
// applyLighting
vec3 applyLighting(vec3 in_color, vec3 position, vec3 normal) {
    vec3 out_color = vec3(0);
    // ambient
    for (uint i = uint(0); i < u_ambient_count; ++i) {
        out_color += u_ambient_lights[i].intensity * u_ambient_lights[i].color * in_color;
    }
    // directional
    for (uint i = uint(0); i < u_directional_count; ++i) {
        float factor = clamp(dot(u_directional_lights[i].direction, -normal), 0, 1);
        out_color += factor * u_directional_lights[i].intensity * u_directional_lights[i].color * in_color;
    }
    return out_color;
}
)"""";

	// UniformBlock3D
	struct UniformBlock3D {
		// UniformBlock3D
		UniformBlock3D() {
			set({});
		}

		// set
		void set(const SceneData& scene_data) {
			const auto& [transform, camera] = scene_data.camera;
			auto view = transform ? transform->calcLocalViewMatrix() : identity<float32, 4>();
			auto proj = camera ? camera->calcProjectionMatrix(1080.0F / 720.0F) : identity<float32, 4>();
			List<Tuple<
				float32,
				Vec3<float32>
				>> ambient_lights;
			List<Tuple<
				Vec3<float32>,
				float32,
				Vec3<float32>>
				> directional_lights;
			for (auto [transform, light_source] : scene_data.lights) {
				if (std::holds_alternative<AmbientLight>(light_source->value)) {
					auto& ambient_light = std::get<AmbientLight>(light_source->value);
					ambient_lights.emplace_back(
						std::make_tuple(
							ambient_light.intensity,
							Vec3<float32>(ambient_light.color) / 255.0F
						)
					);
				}
				if (std::holds_alternative<DirectionalLight>(light_source->value)) {
					auto& directional_light = std::get<DirectionalLight>(light_source->value);
					directional_lights.emplace_back(
						std::make_tuple(
							directional_light.direction,
							directional_light.intensity,
							Vec3<float32>(directional_light.color) / 255.0F
						)
					);
				}
			}
			_bytes = createSTD140(
				std::make_tuple(
					// world_to_clip
					proj * view, // u_world_to_clip

					// light
					// :: ambient
					ambient_lights.size(), // u_ambient_count
					embedList<MAX_LIGHT_COUNT>(ambient_lights), // u_ambient_lights
					// :: directional
					directional_lights.size(), // u_directional_count
					embedList<MAX_LIGHT_COUNT>(directional_lights) // u_directional_lights
				)
			);
		}

		// getSize
		usize getSize() const {
			return _bytes.size();
		}
		// getBuffer
		const uchar* getBuffer() const {
			return _bytes.data();
		}
	private:
		template<usize N, class T>
		static Array<T, N> embedList(const List<T>& list) {
			Array<T, N> out;
			for (usize i = 0; i < list.size(); ++i) {
				out.at(i) = list.at(i);
			}
			return out;
		}

		List<uchar> _bytes;
	};
}