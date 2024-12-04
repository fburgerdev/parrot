#include "common.hh"
#include "camera.hh"
#include "debug/debug.hh"

namespace Parrot {
	// calcProjectionMatrix
	// :: perspective
	Mat4x4<float32> PerspectiveCamera::calcProjectionMatrix(float32 aspect) const {
		Mat4x4<float32> proj_mat = zeros<float32, 4>();
		float32 tan_fov = 1.0F / std::tan(fov / 2);
		proj_mat.at(0, 0) = tan_fov;
		proj_mat.at(1, 1) = tan_fov * aspect;
#if 0
		// clip z to [0, 1] for future graphics apis
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
	Mat4x4<float32> OrthographicCamera::calcProjectionMatrix(float32 aspect) const {
		Mat4x4<float32> proj_mat = zeros<float32, 4>();
		proj_mat.at(0, 0) = 1.0F / scale;
		proj_mat.at(1, 1) = aspect / scale;
#if 0
		// clip z to [0, 1] for future graphics apis
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

	// Camera
	Camera::Camera(const PerspectiveCamera& value)
		: value(value) {}
	Camera::Camera(const OrthographicCamera& value)
		: value(value) {}
	// calcProjectionMatrix
	Mat4x4<float32> Camera::calcProjectionMatrix(float32 aspect) const {
		return std::visit([=](const auto& specific_camera) {
			return specific_camera.calcProjectionMatrix(aspect);
		}, value);
	}
	// getComponentID
	usize Camera::getComponentID() const {
		return typeid(Camera).hash_code();
	}
	// createComponent
	UniquePtr<Component> Camera::createComponent(Entity& entity) const {
		return std::make_unique<CameraComponent>(*this, entity);
	}

	// update
	void CameraComponent::update([[maybe_unused]] float32 delta_time) {
		LOG_ECS_TRACE("camera-component update: {}", *this);
	}

	// <<
	ostream& operator<<(ostream& stream, const PerspectiveCamera& camera) {
		return stream << "PerspectiveCamera(fov=" << camera.fov << ",zrange=" << camera.z_range << ')';
	}
	ostream& operator<<(ostream& stream, const OrthographicCamera& camera) {
		return stream << "OrthographicCamera(scale=" << camera.scale << ",zrange=" << camera.z_range << ')';
	}
	ostream& operator<<(ostream& stream, const Camera& camera) {
		std::visit([&](const auto& specific_camera) {
			stream << specific_camera;
		}, camera.value);
		return stream;
	}
}