#pragma once
#include "window_config.hh"
#include "window_event.hh"

#if defined(PARROT_GLFW)
#include "glfw/physical_window_glfw.hh"
namespace Parrot {
  using PhysicalWindow = GLFW::PhysicalWindow;
}
#endif

namespace Parrot {
  // Window
  class Window : public Scriptable {
  public:
    // (constructor)
    Window(const WindowConfig& config, Scriptable* parent = nullptr);
    Window(Window&&) = default;
    // (destructor)
    ~Window();
    // (assignment)
    Window& operator=(Window&&) = default;

    // getTitle
    const string& getTitle(); /* PARROT_API */
    // setIcon (tray icon)
    void setIcon(const uchar* bytes, uint width, uint height); /* PARROT_API */

    // isOpen
    bool isOpen() const; /* PARROT_API */
    // close
    void close(); /* PARROT_API */

    // setCursorState
    void setCursorState(CursorState state); /* PARROT_API */
    // getCursorCoords
    Vec2<> getCursorCoords() const; /* PARROT_API */

    // bind
    void bind();
    // unbind
    void unbind();

    // pollEvents
    List<WindowEvent> pollEvents();
    // swapBuffers
    void swapBuffers();

    // foreachChild (impl. Scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;
  private:
    string _title;
    uint _width = 0, _height = 0;
    CursorState _cursor = CursorState::NORMAL;
    PhysicalWindow _physical;
  };
}