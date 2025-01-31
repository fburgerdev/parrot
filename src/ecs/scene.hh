#pragma once
#include "scene_config.hh"
#include "entity.hh"

namespace Parrot {
  // Scene
  class Scene : public UUIDObject, public Scriptable {
  public:
    // (constructor)
    Scene(const SceneConfig& config, Scriptable* parent = nullptr);
    Scene(Scene&&) = default;
    // (destructor)
    ~Scene();
    // (assignment)
    Scene& operator=(Scene&&) = default;

    // foreachChild (scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    // update
    void update(float32 delta_time);

    // queryEntities
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

    // name, root
    string name;
    Entity root;
  };
}