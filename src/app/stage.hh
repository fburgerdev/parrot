#pragma once
#include "stage_config.hh"
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/renderer.hh"

namespace Parrot {
  // Stage
  class Stage : public Scriptable {
  public:
    // (constructor)
    Stage(
      const StageConfig& stage_config, Scriptable* parent, AssetAPI& asset_api
    );

    // update
    void update(float32 delta_time);
    // render
    void render();

    // foreachChild (impl. Scriptable)
    void foreachChild(Func<void(Scriptable&)> func);
    void foreachChild(Func<void(const Scriptable&)> func) const;

    // window, scene_layers
    Window window; /* PARROT_API */
    List<Pair<Scene, Renderer>> scene_layers; /* PARROT_API */
  private:
    GPUContext _gpu_context;
  };
}