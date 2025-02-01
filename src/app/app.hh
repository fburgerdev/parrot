#pragma once
#include "default_scriptable.hh"
#include "playing_unit.hh"
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

    // units
    // :: get (by window)
    PlayingUnit& getPlayingUnit(const Window& window);
    const PlayingUnit& getPlayingUnit(const Window& window) const;
    // :: get (by scene)
    PlayingUnit& getPlayingUnit(const Scene& scene);
    const PlayingUnit& getPlayingUnit(const Scene& scene) const;
    // :: add
    PlayingUnit& addPlayingUnit(
      const WindowConfig& window_config, const SceneConfig& scene_config
    );

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
    PlayingUnit* _main_unit = nullptr;
    Map<UUID, PlayingUnit> _units;
    AssetManager _asset_manager;
    DefaultScriptable _default_scriptable;
  };
}