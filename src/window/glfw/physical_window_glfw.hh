#pragma once
#include "window/window_event.hh"
#include "utils/math_matrix.hh"

namespace Parrot {
  namespace GLFW {
    class PhysicalWindow {
    public:
      PhysicalWindow() = default;
      PhysicalWindow(const PhysicalWindow&) = delete;
      PhysicalWindow(PhysicalWindow&& other) noexcept;
      ~PhysicalWindow();
      PhysicalWindow& operator=(const PhysicalWindow&) = delete;
      PhysicalWindow& operator=(PhysicalWindow&& other) noexcept;
  
      bool open(uint width, uint height, strview title);
      void close();
      bool isOpen() const;

      void setIcon(const uchar* bytes, uint width, uint height);

      void setCursorStateNormal();
      void setCursorStateHidden();
      void setCursorStateCaptured();
      Vec2<> getCursorCoords() const;

      List<WindowEvent> pollEvents();
      void swapBuffers();
      void bind();
      void unbind();
    private:
      void* _handle = nullptr;
    };
  }
}