#pragma once
#include "ecs/component.hh"
#include "math/matrix.hh"

namespace Parrot {
	// CameraType
	enum class CameraType {
		PERSPECTIVE, ORTHOGRAPHIC
	};

	// PerspectiveCamera
	struct PerspectiveCamera {
		// calcProjectionMatrix
		Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

		// fov, z_range
		float32 fov = 3.1415926F / 2.0F; // 90°
		Vec2<float32> z_range = { 0.01F, 10000.0F };
	};
	// OrthographicCamera
	struct OrthographicCamera {
		// calcProjectionMatrix
		Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

		// scale, z_range
		float32 scale = 1.0F;
		Vec2<float32> z_range = { 0.01F, 10000.0F };
	};

	// CameraComponent
	class CameraComponent : public Component {
		// CameraComponent
		CameraComponent(Entity& entity, const PerspectiveCamera& camera);
		CameraComponent(Entity& entity, const OrthographicCamera& camera);

		// calcProjectionMatrix
		Mat4x4<float32> calcProjectionMatrix(float32 aspect) const;

		// camera
		Variant<PerspectiveCamera, OrthographicCamera> camera;
	};
}