#pragma once
#include "core/uuid.hh"
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
  class Window : public UUIDObject, public Scriptable {
  public:
    // (constructor)
    Window(const WindowConfig& config, Scriptable* parent = nullptr);
    Window(Window&&) = default;
    // (destructor)
    ~Window();
    // (assignment)
    Window& operator=(Window&&) = default;

    // getTitle
    const string& getTitle();
    // setIcon (tray icon)
    void setIcon(const uchar* bytes, uint width, uint height);

    // isOpen
    bool isOpen() const;
    // close
    void close();

    // setCursorState
    void setCursorState(CursorState state);
    // getCursorCoords
    Vec2<> getCursorCoords() const;

    // foreachChild (impl. Scriptable)
    virtual void foreachChild(
      Func<void(Scriptable&)> func
    ) override;
    virtual void foreachChild(
      Func<void(const Scriptable&)> func
    ) const override;

    // bind
    void bind();
    // unbind
    void unbind();

    // pollEvents
    List<WindowEvent> pollEvents();
    // swapBuffers
    void swapBuffers();
  private:
    string _title;
    uint _width = 0, _height = 0;
    CursorState _cursor = CursorState::NORMAL;
    PhysicalWindow _physical;
  };
}