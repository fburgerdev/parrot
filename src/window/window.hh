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
  class Window : public Scriptable {
  public:
    Window(const WindowConfig& config, Scriptable* parent = nullptr);
    Window(Window&&) = default;
    ~Window();
    Window& operator=(Window&&) = default;

    const string& getTitle();
    void setIcon(const uchar* bytes, uint width, uint height);

    bool isOpen() const;
    void close();

    void setCursorState(CursorState state);
    Vec2<> getCursorCoords() const;

    void bind();
    void unbind();

    List<WindowEvent> pollEvents();
    void swapBuffers();

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