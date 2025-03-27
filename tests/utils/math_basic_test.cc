#include <gtest/gtest.h>
#include "utils/math_basic.hh"
using namespace Parrot;

// clamp
TEST(MathBasicTest, clamp) {
	EXPECT_EQ(clamp(+0.0, +0.0, +1.0), +0.0);
	EXPECT_EQ(clamp(+0.5, +0.0, +1.0), +0.5);
	EXPECT_EQ(clamp(+1.0, +0.0, +1.0), +1.0);

	EXPECT_EQ(clamp(+2.0, -1.0, +1.0), +1.0);
	EXPECT_EQ(clamp(-2.0, -1.0, +1.0), -1.0);

	EXPECT_EQ(clamp(+0.0F, +0.0F, +1.0F), +0.0F);
	EXPECT_EQ(clamp(+0.5F, +0.0F, +1.0F), +0.5F);
	EXPECT_EQ(clamp(+1.0F, +0.0F, +1.0F), +1.0F);

	EXPECT_EQ(clamp(+2.0F, -1.0F, +1.0F), +1.0F);
	EXPECT_EQ(clamp(-2.0F, -1.0F, +1.0F), -1.0F);
}

// min
TEST(MathBasicTest, min) {
	EXPECT_EQ(min(1, 2, 3), 1);
	EXPECT_EQ(min(3, 2, 1), 1);

	EXPECT_EQ(min(float(3), double(2), int(1)), 1);
	EXPECT_EQ(min(double(3), int(2), float(1)), 1);
	EXPECT_EQ(min(int(3), float(2), double(1)), 1);
}
// max
TEST(MathBasicTest, max) {
	EXPECT_EQ(max(1, 2, 3), 3);
	EXPECT_EQ(max(3, 2, 1), 3);

	EXPECT_EQ(max(float(1), double(2), int(3)), 3);
	EXPECT_EQ(max(double(1), int(2), float(3)), 3);
	EXPECT_EQ(max(int(1), float(2), double(3)), 3);
}

// pow
TEST(MathBasicTest, pow) {
	EXPECT_EQ(pow(0, 0), 1);
	EXPECT_EQ(pow(0, 1), 0);

	EXPECT_EQ(pow(2, 0), 1);
	EXPECT_EQ(pow(2, 1), 2);
	EXPECT_EQ(pow(2, 2), 4);
	EXPECT_EQ(pow(2, 3), 8);

	EXPECT_FLOAT_EQ(pow(SQRT_2<>, 2), 2);
	EXPECT_FLOAT_EQ(pow(SQRT_2<>, 4), 4);
}