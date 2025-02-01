#pragma once
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/renderer.hh"

namespace Parrot {
  //? reconsider name
  // PlayingUnit
  class PlayingUnit : public UUIDObject {
  public:
    // (constructor)
    PlayingUnit(
      const WindowConfig& window_config, const SceneConfig& scene_config, 
      Scriptable* parent, AssetAPI& asset_api
    );
    PlayingUnit(PlayingUnit&& other) noexcept;
    // (assignment)
    PlayingUnit& operator=(PlayingUnit&& other) noexcept;

    // draw
    void draw();

    // friend
    friend class App;

    // window, scene
    Window window;
    Scene scene;
  private:
    Renderer _renderer;
    GPUContext _gpu_context;
  };
}