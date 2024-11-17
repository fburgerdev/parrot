#include "common.hh"
#include "stopwatch.hh"
#include <chrono>

using namespace std::chrono;
namespace Parrot {
	// Stopwatch
	Stopwatch::Stopwatch()
		: _begin(steady_clock::now().time_since_epoch().count()) {}
	// reset
	seconds Stopwatch::reset() {
		uint64 end = steady_clock::now().time_since_epoch().count();
		return float32(end - std::exchange(_begin, end)) / 1'000'000'000;
	}
}