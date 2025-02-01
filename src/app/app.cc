#include "common.hh"
#include "app.hh"
#include "app_config.hh"
#include "debug/engine_logger.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
  // (constructor)
  App::App(const stdf::path& app_path)
    : Scriptable(&_default_scriptable), _default_scriptable(*this) {
    AppConfig raw_config = AppConfig(AssetPath(app_path));
    LOG_APP_INFO("creating app '{}' from {}", raw_config.name, app_path);
    // name
    _name = raw_config.name;
    // asset-manager
    _asset_manager = AssetManager(
      raw_config.asset_dir,
      raw_config.loading_policy, raw_config.unloading_policy
    );
    // main (window / scene)
    AppConfig config = AppConfig(AssetPath(app_path), _asset_manager);
    _main_unit = &addPlayingUnit(
      *config.main_window.lock(), *config.main_scene.lock()
    );
  }
  // (destructor)
  App::~App() {
    Scriptable::removeAllScripts();
    for (auto& [uuid, unit] : _units) {
      unit.scene.removeAllScripts();
      unit.window.removeAllScripts();
    }
  }

  // units
  // :: get (by window)
  PlayingUnit& App::getPlayingUnit(const Window& window) {
    for (auto& [uuid, unit] : _units) {
      if (&unit.window == &window) {
        return unit;
      }
    }
    throw std::runtime_error("playing-unit not found");
  }
  const PlayingUnit& App::getPlayingUnit(const Window& window) const {
    for (const auto& [uuid, unit] : _units) {
      if (&unit.window == &window) {
        return unit;
      }
    }
    throw std::runtime_error("playing-unit not found");
  }
  // :: get (by scene)
  PlayingUnit& App::getPlayingUnit(const Scene& scene) {
    for (auto& [uuid, unit] : _units) {
      if (&unit.scene == &scene) {
        return unit;
      }
    }
    throw std::runtime_error("playing-unit not found");
  }
  const PlayingUnit& App::getPlayingUnit(const Scene& scene) const {
    for (const auto& [uuid, unit] : _units) {
      if (&unit.scene == &scene) {
        return unit;
      }
    }
    throw std::runtime_error("playing-unit not found");
  }
  // :: add
  PlayingUnit& App::addPlayingUnit(
    const WindowConfig& window, const SceneConfig& scene
  ) {
    LOG_APP_INFO(
      "creating playing-unit ('{}', '{}') in app '{}'",
      window.title, scene.name, _name
    );
    PlayingUnit unit(window, scene, this);
    unit.window.setIcon(
      Image(_asset_manager.getAssetDirectory() / "default/parrot.png")
    );
    auto result = _units.emplace(unit.getUUID(), std::move(unit));
    return result.first->second;
  }

  // run (game loop)
  void App::run(seconds timeout) {
    if (_main_unit) {
      LOG_APP_INFO("running app '{}'", _name);
      Stopwatch total_watch, frame_watch;
      while (_main_unit->window.isOpen()) {
        seconds delta_time = frame_watch.reset();
        LOG_APP_TRACE("updating app '{}'", _name);
        for (auto& [uuid, unit] : _units) {
          // update scene
          unit.scene.update(delta_time);
          // draw
          unit.draw();
          // swap + update window
          unit.window.swapBuffers();
          for (auto& e : unit.window.pollEvents()) {
            LOG_WINDOW_TRACE("raising event: {}", e);
            unit.window.raiseEvent(e);
          }
        }
        // timeout
        if (timeout && timeout < total_watch.elapsed()) {
          _main_unit->window.close();
        }
      }
      LOG_APP_INFO("terminating app '{}' (gracefully)", _name);
    }
  }

  // foreachChild
  void App::foreachChild(Func<void(Scriptable&)> func) {
    for (auto& [uuid, unit] : _units) {
      func(unit.window);
      func(unit.scene);
    }
  }
  void App::foreachChild(Func<void(const Scriptable&)> func) const {
    for (const auto& [uuid, unit] : _units) {
      func(unit.window);
      func(unit.scene);
    }
  }
}