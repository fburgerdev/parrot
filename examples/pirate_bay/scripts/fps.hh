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
  class FPS : public WindowScript {
  public:
    // (constructor)
    FPS(Window& window)
      : WindowScript(window) {}
    
    // onAttach
    virtual void onAttach() override {
      //_captured = true;
      //window->setCursorState(CursorState::CAPTURED);
      //raiseEvent(FPSEvent(true, window));
    }
    // onDetach
    virtual void onDetach() override {
      _captured = false;
      window->setCursorState(CursorState::NORMAL);
      raiseEvent(FPSEvent(false, window));
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
                window->setCursorState(CursorState::NORMAL);
                raiseEvent(FPSEvent(false, window));
              }
              else {
                window->close();
              }
              return true;
            }
          }
        }
        else if (auto* mp = we->getMousePress()) {
          if (mp->state == MouseState::PRESSED) {
            if (mp->button == MouseButton::LEFT) {
              if (!_captured) {
                _captured = true;
                window->setCursorState(CursorState::CAPTURED);
                raiseEvent(FPSEvent(true, window));
                return true;
              }
            }
          }
        }
        raiseEvent(FPSEvent(_captured, window));
        return false;
      }
      return false;
    }
  private:
    bool _captured = false;
  };
}