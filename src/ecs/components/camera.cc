#include "common.hh"
#include "camera.hh"

namespace Parrot {
	// CameraComponent
	CameraComponent::CameraComponent(Entity& entity, const PerspectiveCamera& camera)
		: Component(entity), camera(camera) {}
	CameraComponent::CameraComponent(Entity& entity, const OrthographicCamera& camera)
		: Component(entity), camera(camera) {}

	// calcProjectionMatrix
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
	Mat4x4<float32> CameraComponent::calcProjectionMatrix(float32 aspect) const {
		return std::visit([=](const auto& value) {
			return value.calcProjectionMatrix(aspect);
		}, camera);
	}
}