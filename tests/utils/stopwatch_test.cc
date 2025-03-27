#include <gtest/gtest.h>
#include "utils/stopwatch.hh"
#include <chrono>
#include <thread>
using namespace Parrot;

// Note: the following tests success depends on the processors speed
// elapsed
TEST(StopwatchTest, elapsed) {
	Stopwatch stopwatch;
	EXPECT_LT(stopwatch.elapsed(), 0.1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	EXPECT_GT(stopwatch.elapsed(), 0.1);
}
// reset
TEST(StopwatchTest, reset) {
	Stopwatch stopwatch;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	stopwatch.reset();
	EXPECT_LT(stopwatch.elapsed(), 0.1);
}