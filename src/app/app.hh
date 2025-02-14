#pragma once
#include "default_scriptable.hh"
#include "stage.hh"
#include "asset/asset_manager.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
  // App
  class App : public Scriptable {
  public:
    // (constructor)
    App(const stdf::path& app_path);
    App(const App&) = delete;
    App(App&&) = default;
    // (destructor)
    ~App();
    // (assignment)
    App& operator=(const App&) = delete;
    App& operator=(App&&) = default;

    // run (game loop)
    void run(seconds timeout = 0);

    // foreachChild (impl. Scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;
  private:
    string _name;
    Stage* _main_stage = nullptr;
    AssetManager _asset_manager;
    DefaultScriptable _default_scriptable;
  };
}