#pragma once
#include "math_matrix.hh"
#include <random>

namespace Parrot {
	// RandomGenerator
	template<class T = DefaultFloat>
	class RandomGenerator {
	public:
		// (constructor)
		RandomGenerator()
			: _generator(_device()) {}

		// random
		// :: 1D
		T random(T min = 0.0, T max = 1.0) {
			std::uniform_real_distribution<T> dist(min, max);
			return dist(_generator);
		}
		// :: 2D
		Vec2<T> random2() {
			return normalized(Vec2<T>(random(), random()));
		}
		// :: 3D
		Vec3<T> random3() {
			return normalized(Vec3<T>(random(), random(), random()));
		}
		// :: 4D
		Vec4<T> random4() {
			return normalized(Vec4<T>(random(), random(), random(), random()));
		}
	private:
		std::random_device _device;
		std::mt19937 _generator;
	};
}