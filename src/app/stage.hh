#pragma once
#include "stage_config.hh"
#include "window/window.hh"
#include "ecs/scene.hh"
#include "graphics/renderer.hh"

namespace Parrot {
  RenderData getRenderData(Scene& scene);
  
  /// @ingroup PublicAPI
  /// @brief Presents Scenes on a Window using layers.
  class Stage : public Scriptable {
  public:
    /// @brief Construct a Stage based on a Stage Config.
    /// @param config StageConfig the Stage is created from
    /// @param parent Parent Scriptable used for propagating events
    /// @param asset_api For usage by the client in EntityScripts
    Stage(const StageConfig& config, Scriptable* parent, AssetAPI& api);

    /// @brief Update all Scenes of the Stage.
    /// @param delta_time Seconds elapsed since last update
    void update(float32 delta_time);
    /// @brief Render the contents of all Scenes on the window (layered).
    void render();

    /// @brief Iterate over every Scene and the Window as Scriptable.
    /// @param func Callback function called for every child Scriptable
    void foreachChild(Func<void(Scriptable&)> func);
    /// @brief Iterate over every Scene and the Window as Scriptable.
    /// @param func Callback function called for every child Scriptable
    void foreachChild(Func<void(const Scriptable&)> func) const;

    /// @brief The Window where the contents of the Scenes are presented.
    Window window;
    /// @brief Layered Scenes with their respective Renderer.
    List<Pair<Scene, Renderer>> scene_layers;
  private:
    GPUContext _gpu_context;
  };
}