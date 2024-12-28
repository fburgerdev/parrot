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
		// elapsed
		seconds elapsed() const;
		// reset
		seconds reset();
	private:
		uint64 _begin = 0;
	};

	// (global) global_watch
	inline const Stopwatch g_global_watch;
}