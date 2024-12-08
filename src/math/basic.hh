#pragma once
#include "common.hh"

namespace Parrot {
	// default
	using DefaultFloat = float32;

	// constants
	// :: PI
	template<class T = DefaultFloat>
	constexpr T PI;
	template<>
	constexpr float32 PI<float32> = 3.1415926F;
	template<>
	constexpr float64 PI<float64> = 3.1415926;

	// clamp
	template<class T = DefaultFloat>
	T clamp(T value, T min, T max) {
		return (value < min ? min : (value > max ? max : value));
	}
}