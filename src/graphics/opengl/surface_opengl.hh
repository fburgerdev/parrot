#pragma once
#include "graphics/scene_data.hh"
#include "graphics/shader_source.hh"
#include "std140_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    // MAX_LIGHT_COUNT
    constexpr uint MAX_LIGHT_COUNT = 50; // needs to match with shader snippet!
    // (global) surface_snippet
    extern const ShaderSource g_surface_snippet;

    // SurfaceBlock
    struct SurfaceBlock {
      // (constructor)
      SurfaceBlock() {
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
            uint32(ambient_lights.size()), // u_ambient_count
            embedList<MAX_LIGHT_COUNT>(ambient_lights), // u_ambient_lights
            // :: directional
            uint32(directional_lights.size()), // u_directional_count
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
}