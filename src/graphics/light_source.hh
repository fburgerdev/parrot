#pragma once
#include "core/asset_handle.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  // AmbientLight
  struct AmbientLight {
    // intensity, color
    DefaultFloat intensity = 1;
    Vec3<uint8> color = { 255, 255, 255 };
  };
  // DirectionalLight
  struct DirectionalLight {
    // direction, intensity, color
    Vec3<DefaultFloat> direction;
    DefaultFloat intensity = 1;
    Vec3<uint8> color = { 255, 255, 255 };
  };
  // PointLight
  struct PointLight {
    // position, range, intensity, color
    Vec3<DefaultFloat> position;
    DefaultFloat range, intensity = 1;
    Vec3<uint8> color = { 255, 255, 255 };
  };
  // SpotLight
  struct SpotLight {
    // position, direction, angle, intensity, color
    Vec3<DefaultFloat> position, direction;
    DefaultFloat angle = PI<> / 2, intensity = 1;
    Vec3<uint8> color = { 255, 255, 255 };
  };

  // LightSource
  class LightSource : public Asset {
  public:
    // (constructor) for SubAsset
    template<JsonType JSON>
    LightSource(
      const JSON& json,
      const AssetPath& asset_path,
      [[maybe_unused]] AssetAPI& asset_api
    ) : Asset(asset_path) {
      loadFromJSON(json);
    }

    // loadFromJSON
    template<JsonType JSON>
    void loadFromJSON(const JSON& json) {
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
      AmbientLight,
      DirectionalLight,
      PointLight,
      SpotLight
    > value;
  };
  // <<
  ostream& operator<<(ostream& stream, const AmbientLight& light);
  ostream& operator<<(ostream& stream, const DirectionalLight& light);
  ostream& operator<<(ostream& stream, const PointLight& light);
  ostream& operator<<(ostream& stream, const SpotLight& light);
  ostream& operator<<(ostream& stream, const LightSource& source);
}