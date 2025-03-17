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
    List<Entity*> queryEntities() {
      List<Entity*> found;
      Stack<Entity*> stack({ &root });
      while (!stack.empty()) {
        Entity* top = stack.top();
        stack.pop();
        if (top->hasComponent<T>()) {
          found.push_back(top);
        }
        top->foreachChild([&](Entity& child) {
          stack.push(&child);
        });
      }
      return found;
    }
    template<class T>
    List<const Entity*> queryEntities() const {
      List<const Entity*> found;
      Stack<const Entity*> stack({ &root });
      while (!stack.empty()) {
        const Entity* top = stack.top();
        stack.pop();
        if (top->hasComponent<T>()) {
          found.push_back(top);
        }
        top->foreachChild([&](const Entity& child) {
          stack.push(&child);
        });
      }
      return found;
    }

    // foreachChild (impl.Scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    // name, root, render
    string name; /* API */
    Entity root; /* API */
    Opt<RenderFunc> render = std::nullopt;
  };
}