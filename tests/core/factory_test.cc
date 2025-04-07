#include <gtest/gtest.h>
#include "core/factory.hh"
using namespace Parrot;

// Base
struct Base {
	// value
	int value;
};
// Derived
struct Derived : public Base {
	// (constructor)
	Derived(int value)
		: Base(value) {}
};

//* Factory
// no methods implemented

//* BasicFactory
// create
TEST(BasicFactory, create) {
	auto factory = BasicFactory<Derived, Base>(42);
	factory.create()->value = 0;
	EXPECT_EQ(factory.create()->value, 42);
}