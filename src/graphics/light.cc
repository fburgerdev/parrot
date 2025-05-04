#include "common.hh"
#include "light.hh"

namespace Parrot {
  // (constructor) for Asset
  Light::Light(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToNode(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  Light::Light(const SerialNode& node, const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void Light::loadFromSerialNode(const SerialNode& node, AssetAPI&) {
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

  // << (stream)
  ostream& operator<<(ostream& stream, const AmbientLight& light) {
    stream << "AmbientLight(";
    stream << "intensity=" << light.intensity;
    stream << ',';
    stream << "color=" << light.color;
    stream << ')';
    return stream;
  }
  ostream& operator<<(ostream& stream, const DirectionalLight& light) {
    stream << "DirectionalLight(";
    stream << "direction=" << light.direction;
    stream << ',';
    stream << "intensity=" << light.intensity;
    stream << ',';
    stream << "color=" << light.color;
    stream << ')';
    return stream;
  }
  ostream& operator<<(ostream& stream, const PointLight& light) {
    stream << "PointLight(";
    stream << "position=" << light.position;
    stream << ',';
    stream << "range=" << light.range;
    stream << ',';
    stream << "intensity=" << light.intensity;
    stream << ',';
    stream << "color=" << light.color;
    stream << ')';
    return stream;
  }
  ostream& operator<<(ostream& stream, const SpotLight& light) {
    stream << "SpotLight(";
    stream << "position=" << light.position;
    stream << ',';
    stream << "direction=" << light.direction;
    stream << ',';
    stream << "angle=" << light.angle;
    stream << ',';
    stream << "intensity=" << light.intensity;
    stream << ',';
    stream << "color=" << light.color;
    stream << ')';
    return stream;
  }
  ostream& operator<<(ostream& stream, const Light& source) {
    std::visit([&](const auto& light) {
      stream << light;
    }, source.value);
    return stream;
  }
}