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
    template<JsonType JSON>
    Light(const JSON& json, const AssetPath& path, AssetAPI& api)
      : Asset(path) {
      loadFromJSON(json, api);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json, [[maybe_unused]] AssetAPI& api) {
      // ambient
      if (json.at("type") == "ambient") {
        AmbientLight light;
        // intensity
        if (json.contains("intensity")) {
          light.intensity = json.at("intensity");
        }
        // color
        if (json.contains("color")) {
          light.color = Vec3<uint8>(
            json.at("color")[0],
            json.at("color")[1],
            json.at("color")[2]
          );
        }
        value = light;
      }
      // directional
      else if (json.at("type") == "directional") {
        DirectionalLight light;
        // direction
        light.direction = Vec3<DefaultFloat>(
          json.at("direction")[0],
          json.at("direction")[1],
          json.at("direction")[2]
        );
        // intensity
        if (json.contains("intensity")) {
          light.intensity = json.at("intensity");
        }
        // color
        if (json.contains("color")) {
          light.color = Vec3<uint8>(
            json.at("color")[0],
            json.at("color")[1],
            json.at("color")[2]
          );
        }
        value = light;
      }
      // point
      else if (json.at("type") == "point") {
        PointLight light;
        // position
        light.position = Vec3<DefaultFloat>(
          json.at("position")[0],
          json.at("position")[1],
          json.at("position")[2]
        );
        // range
        if (json.contains("range")) {
          light.range = json.at("range");
        }
        // intensity
        if (json.contains("intensity")) {
          light.intensity = json.at("intensity");
        }
        // color
        if (json.contains("color")) {
          light.color = Vec3<uint8>(
            json.at("color")[0],
            json.at("color")[1],
            json.at("color")[2]
          );
        }
        value = light;
      }
      // spot
      else if (json.at("type") == "spot") {
        SpotLight light;
        // position
        light.position = Vec3<DefaultFloat>(
          json.at("position")[0],
          json.at("position")[1],
          json.at("position")[2]
        );
        // direction
        light.direction = Vec3<DefaultFloat>(
          json.at("direction")[0],
          json.at("direction")[1],
          json.at("direction")[2]
        );
        // angle
        if (json.contains("angle")) {
          light.angle = json.at("angle");
        }
        // intensity
        if (json.contains("intensity")) {
          light.intensity = json.at("intensity");
        }
        // color
        if (json.contains("color")) {
          light.color = Vec3<uint8>(
            json.at("color")[0],
            json.at("color")[1],
            json.at("color")[2]
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