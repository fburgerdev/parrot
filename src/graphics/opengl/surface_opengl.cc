#include "common.hh"
#include "surface_opengl.hh"

namespace Parrot {
  namespace OpenGL {
    // (constructor)
    SurfaceBlock::SurfaceBlock() {
      set({});
    }

    // set
    void SurfaceBlock::set(const RenderData& render_data) {
      const auto& [transform, camera] = render_data.camera;
      auto view = (
        transform ? transform->calcLocalViewMatrix() : identity<float32, 4>()
        );
      auto proj = (
        camera ? camera->calcProjectionMatrix(1080.0F / 720.0F) : (
          identity<float32, 4>()
          )
        );
      List<Tuple<
        float32,
        Vec3<float32>
        >> ambient_lights;
      List<Tuple<
        Vec3<float32>,
        float32,
        Vec3<float32>>
        > directional_lights;
      for (auto [transform, light] : render_data.lights) {
        if (holds<AmbientLight>(light->value)) {
          auto& ambient_light = std::get<AmbientLight>(light->value);
          ambient_lights.emplace_back(
            std::make_tuple(
              ambient_light.intensity,
              Vec3<float32>(ambient_light.color) / 255.0F
            )
          );
        }
        if (holds<DirectionalLight>(light->value)) {
          auto& directional_light = std::get<DirectionalLight>(
            light->value
          );
          directional_lights.emplace_back(
            std::make_tuple(
              directional_light.direction,
              directional_light.intensity,
              Vec3<float32>(directional_light.color) / 255.0F
            )
          );
        }
      }
      _bytes = createSTD140(std::make_tuple(
        // camera
        (transform ? transform->position : Vec3<>(0, 0, 0)), // u_camera_pos
        // world_to_clip
        proj * view, // u_world_to_clip

        // light
        // :: ambient
        uint32(ambient_lights.size()), // u_ambient_count
        embedList<MAX_LIGHT_COUNT>(
          ambient_lights
        ), // u_ambient_lights
        // :: directional
        uint32(directional_lights.size()), // u_directional_count
        embedList<MAX_LIGHT_COUNT>(
          directional_lights
        ) // u_directional_lights
      ));
    }

    // getSize
    usize SurfaceBlock::getSize() const {
      return _bytes.size();
    }
    // getBuffer
    const uchar* SurfaceBlock::getBuffer() const {
      return _bytes.data();
    }
  }
}