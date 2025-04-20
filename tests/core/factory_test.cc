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

//* LambdaFactory
// create
TEST(LambdaFactory, create) {
	auto factory = LambdaFactory<Base>([]() {
		return std::make_unique<Derived>(42);
	});
	factory.create()->value = 0;
	EXPECT_EQ(factory.create()->value, 42);
}

//* CopyFactory
// create
TEST(CopyFactory, create) {
	auto factory = CopyFactory<Derived, Base>(42);
	factory.create()->value = 0;
	EXPECT_EQ(factory.create()->value, 42);
}