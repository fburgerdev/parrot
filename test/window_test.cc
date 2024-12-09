#include "window/window.hh"
#include <gtest/gtest.h>
using namespace Parrot;

TEST(WindowTest, WindowOpens)
{
	// config
	WindowConfig config;
	config.title = "123456789";
	config.width = 123;
	config.height = 456;
	// window
	Window test_window{ config };
	
	// expect
	EXPECT_TRUE(test_window.isOpen());
}