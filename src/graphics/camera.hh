#pragma once
#include "core/asset_handle.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  inline const float32 DEFAULT_FOV = (PI<float32> / 2.0F); // 90deg
  inline const float32 DEFAULT_SCALE = 1.0F;
  inline const Vec2<float32> DEFAULT_ZRANGE = Vec2<float32>(0.01F, 10'000.0F);

  struct PerspectiveCamera {
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    float32 fov = DEFAULT_FOV;
    Vec2<float32> z_range = DEFAULT_ZRANGE;
  };
  struct OrthographicCamera {
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    float32 scale = DEFAULT_SCALE;
    Vec2<float32> z_range = DEFAULT_ZRANGE;
  };
  struct Camera : public Asset {
    Camera(const PerspectiveCamera& value);
    Camera(const OrthographicCamera& value);
    Camera(const AssetPath& path, AssetAPI& api);
    Camera(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);
    Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

    Variant<
      PerspectiveCamera, OrthographicCamera
    > value = PerspectiveCamera();
  };
  ostream& operator<<(ostream& stream, const OrthographicCamera& camera);
  ostream& operator<<(ostream& stream, const PerspectiveCamera& camera);
  ostream& operator<<(ostream& stream, const Camera& camera);
}