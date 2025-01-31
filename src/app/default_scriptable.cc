#include "common.hh"
#include "default_scriptable.hh"
#include "app.hh"

namespace Parrot {
  // DefaultEventHandler
  class DefaultEventHandler : public Script {
  public:
    // (constructor)
    DefaultEventHandler(App& app)
      : _app(&app) {}

    // resolveEvent
    virtual bool resolveEvent(const Event& e) override {
      bool success = false;
      Queue<Scriptable*> queue({ _app });
      if (const WindowEvent* we = dynamic_cast<const WindowEvent*>(&e)) {
        if (auto* wcr = we->getWindowCloseRequest()) {
          LOG_APP_DEBUG("unresolved window-close-request, closing window '{}'...", we->getTargetWindow()->getTitle());
          we->getTargetWindow()->close();
          return true;
        }
      }
      {
        while (!queue.empty()) {
          Scriptable* front = queue.front();
          queue.pop();
          if (front->resolveEvent(e)) {
            success = true;
          }
          else {
            front->foreachChild([&](Scriptable& child) {
              queue.push(&child);
              });
          }
        }
        return success;
      }
      return false;
    }
    // setScriptOwner
    virtual void setScriptOwner(Scriptable* owner) override {
      _app = (App*)owner; //TODO: use c++ style cast
    }
    // raiseEvent
    virtual void raiseEvent(const Event& e) override {
      _app->raiseEvent(e);
    }
  private:
    App* _app;
  };

  // (constructor)
  DefaultScriptable::DefaultScriptable(App& app)
    : _app(app) {
    addScript<DefaultEventHandler>(app);
  }
  // (destructor)
  DefaultScriptable::~DefaultScriptable() {
    Scriptable::removeAllScripts();
  }
  // foreachChild
  void DefaultScriptable::foreachChild(Func<void(Scriptable&)> func) {
    func(_app);
  }
  void DefaultScriptable::foreachChild(Func<void(const Scriptable&)> func) const {
    func(_app);
  }
}