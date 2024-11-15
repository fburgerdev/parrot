#include "common.hh"
#include "uuid.hh"
#include <random>

namespace Parrot {
	// (static)
	static std::random_device s_random;
	static std::uniform_int_distribution<uint64> s_dist;

	// generateUUID
	uuid generateUUID() {
		std::mt19937 rng(s_random());
		return s_dist(rng);
	}
}