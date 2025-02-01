#pragma once
#include "window/window_event.hh"
#include "math/matrix.hh"

namespace Parrot {
  namespace GLFW {
    // PhysicalWindow
    class PhysicalWindow {
    public:
      // (constructor)
      PhysicalWindow() = default;
      PhysicalWindow(const PhysicalWindow&) = delete;
      PhysicalWindow(PhysicalWindow&& other) noexcept;
      // (destructor)
      ~PhysicalWindow();
      // (assignment)
      PhysicalWindow& operator=(const PhysicalWindow&) = delete;
      PhysicalWindow& operator=(PhysicalWindow&& other) noexcept;
  
      // open
      bool open(uint width, uint height, strview title);
      // close
      void close();
      // isOpen
      bool isOpen() const;

      // setIcon (tray icon)
      void setIcon(const uchar* bytes, uint width, uint height);

      // setCursorStateNormal
      void setCursorStateNormal();
      // setCursorStateHidden
      void setCursorStateHidden();
      // setCursorStateCaptured
      void setCursorStateCaptured();
      // getCursorCoords
      Vec2<> getCursorCoords() const;

      // pollEvents
      List<WindowEvent> pollEvents();
      // swapBuffers
      void swapBuffers();
      // bind
      void bind();
      // unbind
      void unbind();
    private:
      void* _handle = nullptr;
    };
  }
}