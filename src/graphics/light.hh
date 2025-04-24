#pragma once
#include "core/asset_handle.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  /// @brief Global light source illuminating all objects uniformly.
  struct AmbientLight {
    /// @trivial
    friend ostream& operator<<(ostream& stream, const AmbientLight& light);

    /// @trivial
    DefaultFloat intensity = 1;
    /// @trivial
    Vec3<uint8> color = { 255, 255, 255 };
  };
  /// @brief Light source illuminating objects based on their surface normals.
  struct DirectionalLight {
    /// @trivial
    friend ostream& operator<<(ostream& stream, const DirectionalLight& light);

    /// @trivial
    Vec3<DefaultFloat> direction = { 0, 0, 1 };
    /// @trivial
    DefaultFloat intensity = 1;
    /// @trivial
    Vec3<uint8> color = { 255, 255, 255 };
  };
  /// @brief Light source illuminating objects close to it
  /// based on their distance to the light.
  struct PointLight {
    /// @trivial
    friend ostream& operator<<(ostream& stream, const PointLight& light);

    /// @trivial
    Vec3<DefaultFloat> position = { 0, 0, 0 };
    /// @brief Maximum distance to the objects the light illuminates.
    DefaultFloat range = 1;
    /// @trivial
    DefaultFloat intensity = 1;
    /// @trivial
    Vec3<uint8> color = { 255, 255, 255 };
  };
  /// @brief Light source illuminating objects in a cone shape,
  /// like a flashlight.
  struct SpotLight {
    /// @trivial
    friend ostream& operator<<(ostream& stream, const SpotLight& light);

    /// @trivial
    Vec3<DefaultFloat> position = { 0, 0, 0 };
    /// @trivial
    Vec3<DefaultFloat> direction = { 0, 0, 1 };
    /// @brief Angle of the cone in which the light illuminates objects.
    DefaultFloat angle = PI<> / 4;
    /// @trivial
    DefaultFloat intensity = 1;
    /// @trivial
    Vec3<uint8> color = { 255, 255, 255 };
  };

  /// @brief One of the following light sources:
  // AmbientLight, DirectionalLight, PointLight, SpotLight.
  class Light : public Asset {
  public:
    Light(const AssetPath& path, AssetAPI& api);
    Light(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    /// @trivial
    friend ostream& operator<<(ostream& stream, const Light& source);

    /// @trivial
    Variant<AmbientLight, DirectionalLight, PointLight, SpotLight> value;
  };
}