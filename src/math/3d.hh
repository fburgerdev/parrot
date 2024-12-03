#pragma once
#include "matrix.hh"

namespace Parrot {
	// calcTranslationMatrix
	template<typename T>
	Mat4x4<T> calcTranslationMatrix(const Vec3<T>& translation) {
		Mat4x4<T> out = identity<T, 4>();
		out.at(0, 3) = translation.x;
		out.at(1, 3) = translation.y;
		out.at(2, 3) = translation.z;
		return out;
	}
	// calcScaleMatrix
	template<typename T>
	Mat4x4<T> calcScaleMatrix(const Vec3<T>& scale) {
		Mat4x4<T> out = identity<T, 4>();
		out.at(0, 0) *= scale.x;
		out.at(1, 1) *= scale.y;
		out.at(2, 2) *= scale.z;
		return out;
	}
	/*
		Note that the following function calcs a matrix that performs rotations in the following order:
		y -> x -> z
		which is the "yaw, pitch, roll" pattern when looking in the +z direction 
	*/
	// calcRotationMatrix (using euler radius)
	template<typename T>
	Mat4x4<T> calcRotationMatrix(const Vec3<T>& euler_rotation) {
		Mat4x4<T> out = zeros<T, 4>();
		T sina = std::sin(euler_rotation.y);
		T cosa = std::cos(euler_rotation.y);
		T sinb = std::sin(euler_rotation.x);
		T cosb = std::cos(euler_rotation.x);
		T sinc = std::sin(euler_rotation.z);
		T cosc = std::cos(euler_rotation.z);

		// row 1
		out.at(0, 0) = cosa * cosc + sina * sinc * sinb;
		out.at(0, 1) = cosa * sinc - sina * sinb * cosc;
		out.at(0, 2) = sina * cosb;
		// row 2
		out.at(1, 0) = -sinc * cosb;
		out.at(1, 1) = cosb * cosc;
		out.at(1, 2) = sinb;
		// row 3
		out.at(2, 0) = -sina * cosc + cosa * sinc * sinb;
		out.at(2, 1) = -sina * sinc - cosa * sinb * cosc;
		out.at(2, 2) = cosa * cosb;
		// row 4
		out.at(3, 3) = 1;
		return out;
	}
}