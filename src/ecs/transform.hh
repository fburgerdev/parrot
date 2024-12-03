#pragma once
#include "math/matrix.hh"

namespace Parrot {
	// Transform
	class Transform {
	public:
		// calcViewMatrix
		Mat4x4<float32> calcViewMatrix() const;

		// position, rotation, scale
		Vec3<float32> position = { 0.0F, 0.0F, 0.0F };
		Vec3<float32> rotation = { 0.0F, 0.0F, 0.0F };
		Vec3<float32> scale = { 1.0F, 1.0F, 1.0F };
	};
}