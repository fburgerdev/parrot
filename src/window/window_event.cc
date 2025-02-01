#include "common.hh"
#include "window_event.hh"

namespace Parrot {
  // getTargetWindow
  Window* WindowEvent::getTargetWindow() const {
    return (Window*)target;
  }
  // getWindowCloseRequest
  WindowCloseRequest* WindowEvent::getWindowCloseRequest() {
    if (holds<WindowCloseRequest>(_value)) {
      return &std::get<WindowCloseRequest>(_value);
    }
    return nullptr;
  }
  const WindowCloseRequest* WindowEvent::getWindowCloseRequest() const {
    if (holds<WindowCloseRequest>(_value)) {
      return &std::get<WindowCloseRequest>(_value);
    }
    return nullptr;
  }
  // getKeyPress
  KeyPress* WindowEvent::getKeyPress() {
    if (holds<KeyPress>(_value)) {
      return &std::get<KeyPress>(_value);
    }
    return nullptr;
  }
  const KeyPress* WindowEvent::getKeyPress() const {
    if (holds<KeyPress>(_value)) {
      return &std::get<KeyPress>(_value);
    }
    return nullptr;
  }
  // getMousePress
  MousePress* WindowEvent::getMousePress() {
    if (holds<MousePress>(_value)) {
      return &std::get<MousePress>(_value);
    }
    return nullptr;
  }
  const MousePress* WindowEvent::getMousePress() const {
    if (holds<MousePress>(_value)) {
      return &std::get<MousePress>(_value);
    }
    return nullptr;
  }
  // getMouseMove
  MouseMove* WindowEvent::getMouseMove() {
    if (holds<MouseMove>(_value)) {
      return &std::get<MouseMove>(_value);
    }
    return nullptr;

  }
  const MouseMove* WindowEvent::getMouseMove() const {
    if (holds<MouseMove>(_value)) {
      return &std::get<MouseMove>(_value);
    }
    return nullptr;
  }

  // <<
  ostream& operator<<(
    ostream& stream, [[maybe_unused]] const WindowCloseRequest& e
  ) {
    return stream << "WindowCloseRequest()";
  }
  ostream& operator<<(ostream& stream, const KeyPress& e) {
    stream << "KeyPress(";
    stream << "action=" << (int)e.code << ",";
    stream << "state=" << (int)e.state << ")";
    return stream;
  }
  ostream& operator<<(ostream& stream, const MousePress& e) {
    stream << "MousePress(";
    stream << "button=" << (int)e.button << ",";
    stream << "state=" << (int)e.state << ")";
    return stream;
  }
  ostream& operator<<(ostream& stream, const MouseMove& e) {
    stream << "MouseMove(";
    stream << "x=" << e.coords.x << ",";
    stream << "y=" << e.coords.y << ")";
    return stream;
  }
  ostream& operator<<(ostream& stream, const WindowEvent& e) {
    if (holds<WindowCloseRequest>(e._value)) {
      return stream << std::get<WindowCloseRequest>(e._value);
    }
    else if (holds<KeyPress>(e._value)) {
      return stream << std::get<KeyPress>(e._value);
    }
    else if (holds<MousePress>(e._value)) {
      return stream << std::get<MousePress>(e._value);
    }
    else if (holds<MouseMove>(e._value)) {
      return stream << std::get<MouseMove>(e._value);
    }
    else {
      return stream << "InvalidWindowEvent()";
    }
  }
}