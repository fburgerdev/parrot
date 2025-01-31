#pragma once
#include "core/scriptable.hh"

namespace Parrot {
  // forward: App
  class App;
  // DefaultScriptable
  class DefaultScriptable : public Scriptable {
  public:
    // (constructor)
    DefaultScriptable(App& app);
    // (destructor)
    ~DefaultScriptable();

    // foreachChild
    virtual void foreachChild(Func<void(Scriptable&)> func) override;
    virtual void foreachChild(Func<void(const Scriptable&)> func) const override;
  private:
    App& _app;
  };
}