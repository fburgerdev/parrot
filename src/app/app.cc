#include "common.hh"
#include "app.hh"
#include "app_config.hh"
#include "core/log.hh"
#include "utils/stopwatch.hh"

namespace Parrot {
  // (constructor)
  App::App(const stdf::path& app_path) {
    AssetPath asset_path(app_path);
    AppConfig raw_config = AppConfig(asset_path);
    asset_path.debug_root = raw_config.asset_dir;
    LOG_APP_INFO("creating app '{}' from {}", raw_config.name, asset_path);
    // name
    _name = raw_config.name;
    // asset-manager
    _asset_manager = AssetManager(
      raw_config.asset_dir,
      raw_config.loading_policy, raw_config.unloading_policy
    );
    // main-stage
    AppConfig config = AppConfig(asset_path, _asset_manager);
    _main_stage = new Stage(*config.main_stage.lock(), this, _asset_manager);
    // :: icon
    static Image default_icon = Image(
      _asset_manager.getAssetDirectory() / ".parrot/parrot.png",
      _asset_manager.getAssetDirectory()
    );
    _main_stage->window.setIcon(
      default_icon.getBytes(),
      default_icon.getWidth(), default_icon.getHeight()
    );
  }
  // (destructor)
  App::~App() {
    Scriptable::removeAllScripts();
    if (_main_stage) {
      _main_stage->removeAllScripts();
    }
  }

  // run (game loop)
  void App::run(seconds timeout) {
    if (_main_stage) {
      LOG_APP_INFO("running app '{}'", _name);
      Stopwatch total_watch, frame_watch;
      while (_main_stage->window.isOpen()) {
        seconds delta_time = frame_watch.reset();
        LOG_APP_TRACE("updating app '{}'", _name);
        // stage
        auto& stage = *_main_stage;
        // :: update
        stage.update(delta_time);
        // :: render
        stage.render();
        // :: swap buffers + poll events
        stage.window.swapBuffers();
        for (auto& e : stage.window.pollEvents()) {
          LOG_WINDOW_TRACE("raising event: {}", e);
          stage.cascadeEvent(e);
          if (!stage.resolveEvent(e)) {
            if (auto* wcr = e.getWindowCloseRequest()) {
              LOG_APP_DEBUG(
                "unresolved window-close-request, closing window '{}'",
                stage.window.getTitle()
              );
              stage.window.close();
            }
          }
        }
        // timeout
        if (timeout && timeout < total_watch.elapsed()) {
          _main_stage->window.close();
        }
      }
      LOG_APP_INFO("terminating app '{}' (gracefully)", _name);
    }
  }

  // foreachChild
  void App::foreachChild(Func<void(Scriptable&)> func) {
    func(*_main_stage);
  }
  void App::foreachChild(Func<void(const Scriptable&)> func) const {
    func(*_main_stage);
  }
}