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
    Light(const SerialNode& node, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromSerialNode(node, api);
    }

    // loadFromSerialNode
    void loadFromSerialNode(const SerialNode& node, [[maybe_unused]] AssetAPI& api) {
      // ambient
      if (node.at("type") == "ambient") {
        AmbientLight light;
        // intensity
        if (node.contains("intensity")) {
          light.intensity = DefaultFloat(node.at("intensity"));
        }
        // color
        if (node.contains("color")) {
          light.color = Vec3<uint8>(
            uint8(node.at("color")[0]),
            uint8(node.at("color")[1]),
            uint8(node.at("color")[2])
          );
        }
        value = light;
      }
      // directional
      else if (node.at("type") == "directional") {
        DirectionalLight light;
        // direction
        light.direction = Vec3<DefaultFloat>(
          DefaultFloat(node.at("direction")[0]),
          DefaultFloat(node.at("direction")[1]),
          DefaultFloat(node.at("direction")[2])
        );
        // intensity
        if (node.contains("intensity")) {
          light.intensity = DefaultFloat(node.at("intensity"));
        }
        // color
        if (node.contains("color")) {
          light.color = Vec3<uint8>(
            uint8(node.at("color")[0]),
            uint8(node.at("color")[1]),
            uint8(node.at("color")[2])
          );
        }
        value = light;
      }
      // point
      else if (node.at("type") == "point") {
        PointLight light;
        // position
        light.position = Vec3<DefaultFloat>(
          DefaultFloat(node.at("position")[0]),
          DefaultFloat(node.at("position")[1]),
          DefaultFloat(node.at("position")[2])
        );
        // range
        if (node.contains("range")) {
          light.range = DefaultFloat(node.at("range"));
        }
        // intensity
        if (node.contains("intensity")) {
          light.intensity = DefaultFloat(node.at("intensity"));
        }
        // color
        if (node.contains("color")) {
          light.color = Vec3<uint8>(
            uint8(node.at("color")[0]),
            uint8(node.at("color")[1]),
            uint8(node.at("color")[2])
          );
        }
        value = light;
      }
      // spot
      else if (node.at("type") == "spot") {
        SpotLight light;
        // position
        light.position = Vec3<DefaultFloat>(
          DefaultFloat(node.at("position")[0]),
          DefaultFloat(node.at("position")[1]),
          DefaultFloat(node.at("position")[2])
        );
        // direction
        light.direction = Vec3<DefaultFloat>(
          DefaultFloat(node.at("direction")[0]),
          DefaultFloat(node.at("direction")[1]),
          DefaultFloat(node.at("direction")[2])
        );
        // angle
        if (node.contains("angle")) {
          light.angle = DefaultFloat(node.at("angle"));
        }
        // intensity
        if (node.contains("intensity")) {
          light.intensity = DefaultFloat(node.at("intensity"));
        }
        // color
        if (node.contains("color")) {
          light.color = Vec3<uint8>(
            uint8(node.at("color")[0]),
            uint8(node.at("color")[1]),
            uint8(node.at("color")[2])
          );
        }
        value = light;
      }
    }

    // value
    Variant<
      AmbientLight, DirectionalLight, PointLight, SpotLight
    > value; /* API */
  };

  // <<
  ostream& operator<<(ostream& stream, const AmbientLight& light);
  ostream& operator<<(ostream& stream, const DirectionalLight& light);
  ostream& operator<<(ostream& stream, const PointLight& light);
  ostream& operator<<(ostream& stream, const SpotLight& light);
  ostream& operator<<(ostream& stream, const Light& source);
}