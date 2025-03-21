#include <gtest/gtest.h>
#include "core/scriptable.hh"
using namespace Parrot;

// TestScript
template<usize SerialNumber>
class TestScript : public Script {
public:
  // (constructor)
  TestScript() = default;
  TestScript(Map<string, usize>& calls)
    : calls(&calls) {}

  // onUpdate
  virtual void onUpdate(float32 delta_time) override {
    if (calls) {
      string call = "update" + std::to_string(SerialNumber);
      call += "(dt=" + std::to_string(int(delta_time)) + ")";
      calls->emplace(std::move(call), calls->size());
    }
  }
  // resolveEvent
  virtual bool resolveEvent(const Event& e) override {
    if (calls) {
      string call = "resolve-event" + std::to_string(SerialNumber);
      calls->emplace(std::move(call), calls->size());
    }
    return SerialNumber % 2;
  }
  // raiseEvent
  virtual void raiseEvent(const Event& e) override {
    if (calls) {
      string call = "raise-event" + std::to_string(SerialNumber);
      calls->emplace(std::move(call), calls->size());
    }
  }

  // name, stream
  string name = "Serial" + std::to_string(SerialNumber);
  strstream* stream = nullptr;
  Map<string, usize>* calls = nullptr;
private:
  // setScriptOwner
  virtual void setScriptOwner(Scriptable* owner) override {
    if (calls) {
      string call = "set-owner" + std::to_string(SerialNumber);
      calls->emplace(std::move(call), calls->size());
    }
  }
  // onAttach / onDetach
  virtual void onAttach() override {
    if (calls) {
      string call = "attach" + std::to_string(SerialNumber);
      calls->emplace(std::move(call), calls->size());
    }
  }
  virtual void onDetach() override {
    if (calls) {
      string call = "detach" + std::to_string(SerialNumber);
      calls->emplace(std::move(call), calls->size());
    }
  }
};

// TestScriptable
class TestScriptable : public Scriptable {
public:
  // (constructor)
  using Scriptable::Scriptable;
  TestScriptable(List<Scriptable*> childs)
    : childs(childs) {}

  // foreachChild (interface)
  virtual void foreachChild(Func<void(Scriptable&)> func) override {
    for (Scriptable* child : childs) {
      func(*child);
    }
  }
  virtual void foreachChild(Func<void(const Scriptable&)> func) const override {
    for (const Scriptable* child : childs) {
      func(*child);
    }
  }

  // childs
  List<Scriptable*> childs;
};

// ScriptableTest
class ScriptableTest : public testing::Test {
public:
  // calls
  Map<string, usize> calls;
};

// update
TEST_F(ScriptableTest, update) {
  TestScriptable scriptable;
  scriptable.addScript<TestScript<1>>(calls);
  scriptable.addScript<TestScript<2>>(calls);
  scriptable.addScript<TestScript<3>>(calls);

  calls.clear();
  scriptable.update(123);
  EXPECT_EQ(calls.size(), 3);
  EXPECT_TRUE(calls.contains("update1(dt=123)"));
  EXPECT_TRUE(calls.contains("update2(dt=123)"));
  EXPECT_TRUE(calls.contains("update3(dt=123)"));
}
// raiseEvent
TEST_F(ScriptableTest, raiseEvent) {
  TestScriptable parent;
  parent.addScript<TestScript<0>>(calls);
  calls.clear();
  parent.raiseEvent(Event());
  EXPECT_EQ(calls.size(), 1);
  EXPECT_TRUE(calls.contains("resolve-event0"));
  EXPECT_EQ(calls.at("resolve-event0"), 0);

  TestScriptable child1 = TestScriptable(&parent);
  child1.addScript<TestScript<1>>(calls);
  calls.clear();
  child1.raiseEvent(Event());
  EXPECT_EQ(calls.size(), 1);
  EXPECT_TRUE(calls.contains("resolve-event1"));
  EXPECT_EQ(calls.at("resolve-event1"), 0);

  TestScriptable child2 = TestScriptable(&parent);
  child2.addScript<TestScript<2>>(calls);
  calls.clear();
  child2.raiseEvent(Event());
  EXPECT_EQ(calls.size(), 2);
  EXPECT_TRUE(calls.contains("resolve-event0"));
  EXPECT_TRUE(calls.contains("resolve-event2"));
  EXPECT_EQ(calls.at("resolve-event0"), 1);
  EXPECT_EQ(calls.at("resolve-event2"), 0);
}
// cascadeEvent
TEST_F(ScriptableTest, cascadeEvent) {
  TestScriptable subchild;
  subchild.addScript<TestScript<0>>(calls);
  TestScriptable child1 = TestScriptable(List<Scriptable*>{ &subchild });
  child1.addScript<TestScript<1>>(calls);
  TestScriptable child2;
  child2.addScript<TestScript<2>>(calls);
  TestScriptable parent = TestScriptable({ &child1, &child2 });
  parent.addScript<TestScript<42>>(calls);
  
  calls.clear();
  parent.cascadeEvent(Event());
  EXPECT_EQ(calls.size(), 3);
  EXPECT_TRUE(calls.contains("resolve-event0"));
  EXPECT_TRUE(calls.contains("resolve-event1"));
  EXPECT_TRUE(calls.contains("resolve-event2"));
}
// resolveEvent
TEST_F(ScriptableTest, resolveEvent) {
  TestScriptable child;
  child.addScript<TestScript<1>>(calls);
  child.addScript<TestScript<2>>(calls);

  calls.clear();
  child.raiseEvent(Event());
  EXPECT_EQ(calls.size(), 2);
  EXPECT_TRUE(calls.contains("resolve-event1"));
  EXPECT_TRUE(calls.contains("resolve-event2"));
}

// script
// :: get
TEST_F(ScriptableTest, getScript) {
  TestScriptable scriptable;
  scriptable.addScript<TestScript<1>>(calls);
  EXPECT_EQ(scriptable.getScript<TestScript<1>>().calls, &calls);
}
// :: add
TEST_F(ScriptableTest, addScript) {
  TestScriptable scriptable;
  
  calls.clear();
  UniquePtr<TestScript<1>> script = std::make_unique<TestScript<1>>(calls);
  scriptable.addScript(Script::getID<TestScript<1>>(), std::move(script));
  EXPECT_EQ(scriptable.getScript<TestScript<1>>().calls, &calls);
  EXPECT_EQ(calls.size(), 1);
  EXPECT_TRUE(calls.contains("attach1"));

  calls.clear();
  scriptable.addScript<TestScript<2>>(calls);
  EXPECT_EQ(scriptable.getScript<TestScript<2>>().calls, &calls);
  EXPECT_EQ(calls.size(), 1);
  EXPECT_TRUE(calls.contains("attach2"));
}
// :: remove
TEST_F(ScriptableTest, removeScript) {
  TestScriptable scriptable;
  scriptable.addScript<TestScript<1>>(calls);

  calls.clear();
  scriptable.removeScript<TestScript<1>>();
  EXPECT_EQ(scriptable.getScriptCount(), 0);
  EXPECT_EQ(calls.size(), 1);
  EXPECT_TRUE(calls.contains("detach1"));
}
// :: remove-all
TEST_F(ScriptableTest, removeAllScripts) {
  TestScriptable scriptable;
  scriptable.addScript<TestScript<1>>(calls);
  scriptable.addScript<TestScript<2>>(calls);
  scriptable.addScript<TestScript<3>>(calls);

  calls.clear();
  scriptable.removeAllScripts();
  EXPECT_EQ(scriptable.getScriptCount(), 0);
  EXPECT_EQ(calls.size(), 3);
  EXPECT_TRUE(calls.contains("detach1"));
  EXPECT_TRUE(calls.contains("detach2"));
  EXPECT_TRUE(calls.contains("detach3"));
}
// :: foreach
TEST_F(ScriptableTest, foreachScript) {
  TestScriptable scriptable;
  Map<const Script*, usize> script_map;
  script_map.emplace(&scriptable.addScript<TestScript<1>>(), 0);
  script_map.emplace(&scriptable.addScript<TestScript<2>>(), 0);
  script_map.emplace(&scriptable.addScript<TestScript<3>>(), 0);
  scriptable.foreachScript([&](Script& script) {
    ++script_map[&script];
  });
  scriptable.foreachScript([&](const Script& script) {
    ++script_map[&script];
  });
  EXPECT_EQ(script_map.size(), 3);
  for (auto [script, count] : script_map) {
    EXPECT_EQ(count, 2);
  }
}