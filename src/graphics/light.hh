#pragma once
#include "core/asset_handle.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  // AmbientLight
  struct AmbientLight {
    // intensity, color
    DefaultFloat intensity /* API */ = 1;
    Vec3<uint8> color /* API */ = { 255, 255, 255 };
  };
  // DirectionalLight
  struct DirectionalLight {
    // direction, intensity, color
    Vec3<DefaultFloat> direction /* API */ = { 0, 0, 1 };
    DefaultFloat intensity /* API */ = 1;
    Vec3<uint8> color /* API */ = { 255, 255, 255 };
  };
  // PointLight
  struct PointLight {
    // position, range, intensity, color
    Vec3<DefaultFloat> position /* API */ = { 0, 0, 0 };
    DefaultFloat range /* API */ = 1;
    DefaultFloat intensity /* API */ = 1;
    Vec3<uint8> color /* API */ = { 255, 255, 255 };
  };
  // SpotLight
  struct SpotLight {
    // position, direction, angle, intensity, color
    Vec3<DefaultFloat> position /* API */ = { 0, 0, 0 };
    Vec3<DefaultFloat> direction /* API */ = { 0, 0, 1 };
    DefaultFloat angle /* API */ = PI<> / 2;
    DefaultFloat intensity /* API */ = 1;
    Vec3<uint8> color /* API */ = { 255, 255, 255 };
  };

  // Light
  class Light : public Asset {
  public:
    // (constructor) for SubAsset
    Light(const AssetPath& path, AssetAPI& api);
    Light(const SerialNode& node, const AssetPath& path, AssetAPI& api);

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, AssetAPI& api);

    // value
    Variant<
      AmbientLight, DirectionalLight, PointLight, SpotLight
    > value; /* API */
  };

  // << (stream)
  ostream& operator<<(ostream& stream, const AmbientLight& light);
  ostream& operator<<(ostream& stream, const DirectionalLight& light);
  ostream& operator<<(ostream& stream, const PointLight& light);
  ostream& operator<<(ostream& stream, const SpotLight& light);
  ostream& operator<<(ostream& stream, const Light& source);
}