#pragma once
#include "scene_config.hh"
#include "entity.hh"

namespace Parrot {
  class Scene;
  class Renderer;
  using RenderFunc = Func<void(Renderer&, Scene&)>;

  class Scene : public Scriptable {
  public:
    Scene(const SceneConfig& config, Scriptable* parent, AssetAPI& asset_api);
    Scene(Scene&&) = default;
    ~Scene();
    Scene& operator=(Scene&&) = default;

    void update(float32 delta_time);

    template<class T>
    List<Entity*> queryEntities();
    template<class T>
    List<const Entity*> queryEntities() const;

    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    string name;
    Entity root;
    Opt<RenderFunc> render = std::nullopt;
  };
}
#include "scene_impl.hh"