#pragma once
#include "common.hh"

namespace Parrot {
	// seconds
	using seconds = float32;

	// Stopwatch
	class Stopwatch {
	public:
		// Stopwatch
		Stopwatch();
		// reset
		seconds reset();
	private:
		uint64 _begin = 0;
	};
}