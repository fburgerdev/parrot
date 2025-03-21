#include <gtest/gtest.h>
#include "core/script.hh"
using namespace Parrot;

// TestScript
class TestScript : public Script {
public:
	// (constructor)
	using Script::Script;

  // raiseEvent
  virtual void raiseEvent(const Event& e) override {
    // do nothing
  }
private:
  // setScriptOwner
  virtual void setScriptOwner(Scriptable* owner) override {
    // do nothing
  }
};
// Script1
class Script1 : public Script {};
// Script2
class Script2 : public Script {};

// resolveEvent
TEST(ScriptTest, resolveEvent) {
  EXPECT_EQ(TestScript().resolveEvent(Event()), false);
}
// getID
TEST(ScriptTest, getID) {
  EXPECT_NE(Script::getID<Script1>(), Script::getID<Script2>());
}