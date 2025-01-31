#pragma once
#include "playing_unit.hh"
#include "default_scriptable.hh"
#include "asset/asset_manager.hh"

namespace Parrot {
  // App
  class App : public Scriptable {
  public:
    // (constructor)
    App(const stdf::path& config_path);
    App(App&&) = default;
    // (destructor)
    ~App();
    // (assignment)
    App& operator=(App&&) = default;

    // add
    PlayingUnit& add(
      const WindowConfig& window_config, const SceneConfig& scene_config
    );
    // getPlayingUnit
    PlayingUnit& getPlayingUnit(const Window& window);
    const PlayingUnit& getPlayingUnit(const Window& window) const;
    PlayingUnit& getPlayingUnit(const Scene& scene);
    const PlayingUnit& getPlayingUnit(const Scene& scene) const;

    // run
    void run();

    // foreachChild
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