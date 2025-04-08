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
    // (constructor)
    Camera(const PerspectiveCamera& value);
    Camera(const OrthographicCamera& value);
    // :: for Asset
    Camera(const AssetPath& path, AssetAPI& api);
    Camera(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    // calcProjectionMatrix
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    // value
    Variant<
      PerspectiveCamera, OrthographicCamera
    > value = PerspectiveCamera();
  };
  // << (stream)
  ostream& operator<<(ostream& stream, const OrthographicCamera& camera);
  ostream& operator<<(ostream& stream, const PerspectiveCamera& camera);
  ostream& operator<<(ostream& stream, const Camera& camera);
}