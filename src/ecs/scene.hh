#pragma once
#include "scene_config.hh"
#include "entity.hh"

namespace Parrot {
  // forward: Scene
  class Scene;
  // forward: Renderer
  class Renderer;
  // RenderFunc
  using RenderFunc = Func<void(Renderer&, Scene&)>;

  // Scene
  class Scene : public Scriptable {
  public:
    // (constructor)
    Scene(const SceneConfig& config, Scriptable* parent, AssetAPI& asset_api);
    Scene(Scene&&) = default;
    // (destructor)
    ~Scene();
    // (assignment)
    Scene& operator=(Scene&&) = default;

    // update
    void update(float32 delta_time);

    // queryEntities
    template<class T>
    List<Entity*> queryEntities();
    template<class T>
    List<const Entity*> queryEntities() const;

    // foreachChild (impl.Scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    // name, root, render
    string name;
    Entity root;
    Opt<RenderFunc> render = std::nullopt;
  };
}
#include "scene_impl.hh"