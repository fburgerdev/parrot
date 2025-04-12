#pragma once

namespace Parrot {
  template<class T>
  List<Entity*> Scene::queryEntities() {
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
  List<const Entity*> Scene::queryEntities() const {
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
}