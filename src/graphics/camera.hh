#pragma once
#include "core/asset_handle.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  // (global) default
  inline const float32 DEFAULT_FOV = (3.1415926F / 2.0F); // 90deg
  inline const float32 DEFAULT_SCALE = 1.0F;
  inline const Vec2<float32> DEFAULT_ZRANGE = Vec2<float32>(0.01F, 10'000.0F);

  // PerspectiveCamera
  struct PerspectiveCamera {
    // calcProjectionMatrix
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    // fov, z_range
    float32 fov /* PARROT_API */ = DEFAULT_FOV;
    Vec2<float32> z_range /* PARROT_API */ = DEFAULT_ZRANGE;
  };
  // OrthographicCamera
  struct OrthographicCamera {
    // calcProjectionMatrix
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    // scale, z_range
    float32 scale /* PARROT_API */ = DEFAULT_SCALE;
    Vec2<float32> z_range /* PARROT_API */ = DEFAULT_ZRANGE;
  };
  // Camera
  struct Camera : public Asset {
    // (constructor)
    Camera(const PerspectiveCamera& value);
    Camera(const OrthographicCamera& value);
    // :: for Asset
    Camera(const AssetPath& path, AssetAPI& api);
    template<JsonType JSON>
    Camera(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, [[maybe_unused]] AssetAPI& api) {
      // z-range
      Vec2<float32> z_range = (
        json.contains("z-range") ? Vec2<float32>(
          json.at("z-range")[0], json.at("z-range")[1]
        ) : DEFAULT_ZRANGE
      );
      // type
      if (!json.contains("type") &&
          json.contains("fov") &&
          json.contains("scale")) {
        throw std::logic_error("couldn't deduce camera type from json");
      }
      // :: perspective
      else if ((json.contains("type") && json.at("type") == "perspective") ||
          (!json.contains("type") && json.contains("fov"))) {
        float32 fov = (
          json.contains("fov") ? float32(json.at("fov")) : DEFAULT_FOV
        );
        value = PerspectiveCamera(fov, z_range);
      }
      // :: orthographic
      else if ((json.contains("type") && json.at("type") == "orthographic") ||
          (!json.contains("type") && json.contains("scale"))) {
        float32 scale = (
          json.contains("scale") ? float32(json.at("scale")) : DEFAULT_SCALE
        );
        value = OrthographicCamera(scale, z_range);
      }
      else {
        throw std::logic_error("unexpected branch");
      }
    }
    // calcProjectionMatrix
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    // value
    Variant<
      PerspectiveCamera, OrthographicCamera
    > value /* PARROT_API */ = PerspectiveCamera();
  };
  // <<
  ostream& operator<<(ostream& stream, const OrthographicCamera& camera);
  ostream& operator<<(ostream& stream, const PerspectiveCamera& camera);
  ostream& operator<<(ostream& stream, const Camera& camera);
}