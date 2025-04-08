#pragma once
#include "stage.hh"
#include "asset/asset_manager.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
  class App : public Scriptable {
  public:
    App(const stdf::path& app_path);
    App(const App&) = delete;
    App(App&&) = default;
    ~App();
    App& operator=(const App&) = delete;
    App& operator=(App&&) = default;

    void run(seconds timeout = 0);

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
  };
}