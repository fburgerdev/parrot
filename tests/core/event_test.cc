#include <gtest/gtest.h>
#include "core/event.hh"
using namespace Parrot;

// getDebugType
TEST(EventTest, getDebugType) {
	EXPECT_EQ(Event().getDebugType(), "Event");
}