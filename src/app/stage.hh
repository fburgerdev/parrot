#pragma once
#include "stage_config.hh"
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/renderer.hh"

namespace Parrot {
  RenderData getRenderData(Scene& scene);
  
  class Stage : public Scriptable {
  public:
    Stage(const StageConfig& config, Scriptable* parent, AssetAPI& api);

    void update(float32 delta_time);
    void render();

    void foreachChild(Func<void(Scriptable&)> func);
    void foreachChild(Func<void(const Scriptable&)> func) const;

    Window window;
    List<Pair<Scene, Renderer>> scene_layers;
  private:
    GPUContext _gpu_context;
  };
}