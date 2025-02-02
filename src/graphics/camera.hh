#pragma once
#include "core/asset_handle.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  // (global) default
  inline const float32 DEFAULT_FOV = (3.1415926F / 2.0F); // 90deg
  inline const float32 DEFAULT_SCALE = 1.0F;
  inline const Vec2<float32> DEFAULT_ZRANGE = Vec2<float32>(0.01F, 10000.0F);

  // PerspectiveCamera
  struct PerspectiveCamera {
    // calcProjectionMatrix
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    // fov, z_range
    float32 fov = DEFAULT_FOV; 
    Vec2<float32> z_range = DEFAULT_ZRANGE;
  };
  // OrthographicCamera
  struct OrthographicCamera {
    // calcProjectionMatrix
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    // scale, z_range
    float32 scale = DEFAULT_SCALE;
    Vec2<float32> z_range = DEFAULT_ZRANGE;
  };
  // Camera
  struct Camera : public Asset {
    // (constructor) for Asset
    Camera(const PerspectiveCamera& value);
    Camera(const OrthographicCamera& value);
    template<JsonType JSON>
    Camera(
      const JSON& json,
      const AssetPath& asset_path,
      [[maybe_unused]] AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json);
    }
    // loadFromJSON
    template<JsonType JSON>
      void loadFromJSON(const JSON& json) {
      Vec2<float32> z_range = (
        json.contains("z-range") ? Vec2<float32>(
          json.at("z-range")[0], json.at("z-range")[1]
        ) : DEFAULT_ZRANGE
      );
      if (!json.contains("type") &&
          json.contains("fov") &&
          json.contains("scale")) {
        throw std::logic_error("couldn't deduce camera type from json");
      }
      else if ((json.contains("type") && json.at("type") == "perspective") ||
          (!json.contains("type") && json.contains("fov"))) {
        float32 fov = (
          json.contains("fov") ? float32(json.at("fov")) : DEFAULT_FOV
        );
        value = PerspectiveCamera(fov, z_range);
      }
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
    Variant<PerspectiveCamera, OrthographicCamera> value = PerspectiveCamera();
  };
  // <<
  ostream& operator<<(ostream& stream, const OrthographicCamera& camera);
  ostream& operator<<(ostream& stream, const PerspectiveCamera& camera);
  ostream& operator<<(ostream& stream, const Camera& camera);
}