#include "common.hh"
#include "camera.hh"
#include "core/log.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // calcProjectionMatrix
  // :: perspective
  Mat4x4<float32> PerspectiveCamera::calcProjectionMatrix(
    float32 aspect
  ) const {
    Mat4x4<float32> proj_mat = zeros<float32, 4>();
    float32 tan_fov = 1.0F / std::tan(fov / 2);
    proj_mat.at(0, 0) = tan_fov;
    proj_mat.at(1, 1) = tan_fov * aspect;
#if 0
    // clip z to [0, 1] for future graphics API's
    proj_mat.at(2, 2) = z_range.y / (z_range.y - z_range.x);
    proj_mat.at(2, 3) = -z_range.x * z_range.y / (z_range.y - z_range.x);
#endif
#if defined(PARROT_OPENGL)
    // clip z to [-1, 1] for OPENGL
    proj_mat.at(2, 2) = 2 * z_range.y / (z_range.y - z_range.x) - 1;
    proj_mat.at(2, 3) = -2 * z_range.x * z_range.y / (z_range.y - z_range.x);
#endif
    proj_mat.at(3, 2) = 1;
    return proj_mat;
  }
  // :: orthographic
  Mat4x4<float32> OrthographicCamera::calcProjectionMatrix(
    float32 aspect
  ) const {
    Mat4x4<float32> proj_mat = zeros<float32, 4>();
    proj_mat.at(0, 0) = 1.0F / scale;
    proj_mat.at(1, 1) = aspect / scale;
#if 0
    // clip z to [0, 1] for future graphics API's
    proj_mat.at(2, 2) = 1 / (z_range.y - z_range.x);
    proj_mat.at(2, 3) = -z_range.x / (z_range.y - z_range.x);
#endif
#if defined(PARROT_OPENGL)
    // clip z to [-1, 1] for OPENGL
    proj_mat.at(2, 2) = 2 / (z_range.y - z_range.x);
    proj_mat.at(2, 3) = -2 * z_range.x / (z_range.y - z_range.x) - 1;
#endif
    proj_mat.at(3, 3) = 1;
    return proj_mat;
  }

  // (constructor)
  Camera::Camera(const PerspectiveCamera& value)
    : value(value) {}
  Camera::Camera(const OrthographicCamera& value)
    : value(value) {}
  // :: for Asset
  Camera::Camera(const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    auto json = path.applySubpathToNode(
      SerialNode::loadFromJSON(path.file)
    );
    loadFromSerialNode(json, api);
  }
  Camera::Camera(const SerialNode& node, const AssetPath& path, AssetAPI& api)
    : Asset(path) {
    loadFromSerialNode(node, api);
  }

  // loadFromSerialNode
  void Camera::loadFromSerialNode(const SerialNode& node, AssetAPI&) {
    // z-range
    Vec2<float32> z_range = (
      node.contains("z-range") ? Vec2<float32>(
        DefaultFloat(node.at("z-range")[0]),
        DefaultFloat(node.at("z-range")[1])
      ) : DEFAULT_ZRANGE
      );
    // type
    if (!node.contains("type") &&
      node.contains("fov") &&
      node.contains("scale")) {
      throw std::logic_error("couldn't deduce camera type from node");
    }
    // :: perspective
    else if ((node.contains("type") && node.at("type") == "perspective") ||
      (!node.contains("type") && node.contains("fov"))) {
      float32 fov = (
        node.contains("fov") ? float32(node.at("fov")) : DEFAULT_FOV
        );
      value = PerspectiveCamera(fov, z_range);
    }
    // :: orthographic
    else if ((node.contains("type") && node.at("type") == "orthographic") ||
      (!node.contains("type") && node.contains("scale"))) {
      float32 scale = (
        node.contains("scale") ? float32(node.at("scale")) : DEFAULT_SCALE
        );
      value = OrthographicCamera(scale, z_range);
    }
    else {
      throw std::logic_error("unexpected branch");
    }
  }

  // calcProjectionMatrix
  Mat4x4<float32> Camera::calcProjectionMatrix(float32 aspect) const {
    return std::visit([=](const auto& specific_camera) {
      return specific_camera.calcProjectionMatrix(aspect);
    }, value);
  }

  // << (stream)
  ostream& operator<<(ostream& stream, const PerspectiveCamera& cam) {
    stream << "PerspectiveCamera(";
    stream << "fov=" << cam.fov << ",";
    stream << "zrange=" << cam.z_range << ")";
    return stream;
  }
  ostream& operator<<(ostream& stream, const OrthographicCamera& cam) {
    stream << "OrthographicCamera(";
    stream << "scale=" << cam.scale << ",";
    stream << "zrange=" << cam.z_range << ")";
    return stream;
  }
  ostream& operator<<(ostream& stream, const Camera& cam) {
    std::visit([&](const auto& specific_cam) {
      stream << specific_cam;
    }, cam.value);
    return stream;
  }
}