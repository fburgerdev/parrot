#pragma once
#include "window/window_event.hh"
#include "utils/image.hh"

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

      // setIcon
      void setIcon(const Image& image);

      // setCursorStateNormal
      void setCursorStateNormal();
      // setCursorStateHidden
      void setCursorStateHidden();
      // setCursorStateCaptured
      void setCursorStateCaptured();

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