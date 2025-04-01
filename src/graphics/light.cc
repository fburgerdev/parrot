#include "common.hh"
#include "light.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // (constructor) for Asset
  Light::Light(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToJSON(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromJSON(json, api);
  }

  // <<
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