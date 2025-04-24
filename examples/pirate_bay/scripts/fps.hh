#pragma once
#include "client.hh"

namespace Parrot {
  // FPSEvent
  struct FPSEvent : public Event {
    // (constructor)
    FPSEvent(bool is_captured, Window* window)
      : Event(window), is_captured(is_captured) {}
    
    // is_captured
    bool is_captured;
  };

  // FPS
  class FPS : public StageScript {
  public:
    // (constructor)
    FPS(Stage& stage)
      : StageScript(stage) {}

    // onDetach
    virtual void onDetach() override {
      _captured = false;
      stage->window.setCursorState(CursorState::NORMAL);
      stage->cascadeEvent(FPSEvent(false, &stage->window));
    }

    // resolveEvent
    virtual bool resolveEvent(const Event& e) override {
      if (const WindowEvent* we = dynamic_cast<const WindowEvent*>(&e)) {
        // capture
        if (auto* kp = we->getKeyPress()) {
          if (kp->state == KeyState::PRESSED) {
            if (kp->code == KeyCode::KEY_ESCAPE) {
              if (_captured) {
                _captured = false;
                stage->window.setCursorState(CursorState::NORMAL);
                raiseEvent(FPSEvent(false, &stage->window));
              }
              else {
                stage->window.close();
              }
              return true;
            }
          }
        }
        else if (auto* mp = we->getMousePress()) {
          if (mp->state == MousePress::State::PRESSED) {
            if (mp->button == MousePress::Button::LEFT) {
              if (!_captured) {
                _captured = true;
                stage->window.setCursorState(CursorState::CAPTURED);
                stage->cascadeEvent(FPSEvent(true, &stage->window));
                return true;
              }
            }
          }
        }
        stage->cascadeEvent(FPSEvent(_captured, &stage->window));
        return false;
      }
      return false;
    }
  private:
    bool _captured = false;
  };
}