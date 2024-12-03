#include "common.hh"
#include "transform.hh"
#include "math/3d.hh"

namespace Parrot {
	// calcViewMatrix
	Mat4x4<float32> Transform::calcViewMatrix() const {
		Mat4x4<float32> translation_matrix = calcTranslationMatrix(-position);
		Mat4x4<float32> rotation_matrix = transposed(calcRotationMatrix(rotation));
		Mat4x4<float32> scale_matrix = calcScaleMatrix(scale);
		return translation_matrix * rotation_matrix * scale_matrix;
	}
}