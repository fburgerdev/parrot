#include "common.hh"
#include "physical_window_glfw.hh"
#include "core/log.hh"
#include <glad/glad.hh>
#include <GLFW/glfw3.h>

namespace Parrot {
  namespace GLFW {
    // HandleGLFW
    using HandleGLFW = GLFWwindow;

    // (static) event_queues
    static Map<HandleGLFW*, List<WindowEvent>> s_event_queues;

    // (static) handle
    static HandleGLFW* handle(void* ptr) {
      return reinterpret_cast<HandleGLFW*>(ptr);
    }

    // (constructor)
    PhysicalWindow::PhysicalWindow(PhysicalWindow&& other) noexcept
      : _handle(std::exchange(other._handle, nullptr)) {}
    // (assignment)
    PhysicalWindow& PhysicalWindow::operator=(
      PhysicalWindow&& other
    ) noexcept {
      _handle = std::exchange(other._handle, nullptr);
      return *this;
    }
    // (destructor)
    PhysicalWindow::~PhysicalWindow() {
      close();
    }

    // open
    bool PhysicalWindow::open(uint width, uint height, strview title) {
      // clean
      if (isOpen()) {
        close();
      }

      // init glfw
      if (!glfwInit()) {
        return false;
      }

      // create window
      glfwWindowHint(GLFW_RESIZABLE, 0);
      _handle = glfwCreateWindow(
        width, height, string(title).c_str(), NULL, NULL
      );
      if (!_handle) {
        glfwTerminate();
        return false;
      }
      s_event_queues.emplace(handle(_handle), List<WindowEvent>());
      bind();
      glfwSwapInterval(1);

      // add callbacks
      glfwSetWindowCloseCallback(handle(_handle), [](HandleGLFW* window) {
        WindowEvent e(WindowCloseRequest({}));
        s_event_queues.at(window).emplace_back(e);
        LOG_WINDOW_TRACE("detected {}", e);
      });
      glfwSetMouseButtonCallback(handle(_handle), [](HandleGLFW* window,
          int button, int action, int
        ) {
        MousePress::Button mouse_button = (
          button == GLFW_MOUSE_BUTTON_LEFT ? MousePress::Button::LEFT : (
            button == GLFW_MOUSE_BUTTON_MIDDLE ? MousePress::Button::MIDDLE : (
              button == GLFW_MOUSE_BUTTON_RIGHT ? MousePress::Button::RIGHT : (
                throw std::logic_error("invalid enum value")
              )
            )
          )
        );
        MousePress::State mouse_state = (
          action == GLFW_PRESS ? MousePress::State::PRESSED : (
            action == GLFW_RELEASE ? MousePress::State::RELEASED : (
              throw std::logic_error("invalid enum value")
            )
          )
        );
        WindowEvent e(MousePress({ mouse_button, mouse_state }));
        s_event_queues.at(window).emplace_back(e);
        LOG_WINDOW_TRACE("detected {}", e);
      });
      glfwSetKeyCallback(handle(_handle), [](HandleGLFW* window,
          int glfw_key, int,
          int glfw_action, int
        ) {
        KeyCode code = (KeyCode)glfw_key;
        KeyState state = (
          glfw_action == GLFW_PRESS ? KeyState::PRESSED : (
            glfw_action == GLFW_RELEASE ? KeyState::RELEASED : (
              glfw_action == GLFW_REPEAT ? KeyState::REPEATED : (
                throw std::logic_error("invalid enum value")
              )
            )
          )
        );
        WindowEvent e(KeyPress({ code, state }));
        s_event_queues.at(window).emplace_back(e);
        LOG_WINDOW_TRACE("detected {}", e);
      });
      glfwSetCursorPosCallback(handle(_handle), [](HandleGLFW* window,
          double glfw_x, double glfw_y
        ) {
          WindowEvent e(
            MouseMove({ Vec2<float32>(float32(glfw_x), float32(glfw_y)) })
          );
          s_event_queues.at(window).emplace_back(e);
          LOG_WINDOW_TRACE("detected {}", e);
      });

      // init glad
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
      }
      return true;
    }
    // close
    void PhysicalWindow::close() {
      if (isOpen()) {
        glfwDestroyWindow(handle(_handle));
        s_event_queues.erase(handle(_handle));
        _handle = nullptr;
      }
    }
    // isOpen
    bool PhysicalWindow::isOpen() const {
      return _handle;
    }

    // setIcon (tray icon)
    void PhysicalWindow::setIcon(const uchar* bytes, uint width, uint height) {
      GLFWimage images[1] = { {
        .width = int(width), //! narrowing conversion
        .height = int(height), //! narrowing conversion
        .pixels = (uchar*)bytes, //! unsafe if glfw modifies bytes
      } };
      glfwSetWindowIcon(handle(_handle), 1, images);
    }

    // setCursorStateNormal
    void PhysicalWindow::setCursorStateNormal() {
      if (_handle) {
        glfwSetInputMode(handle(_handle), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      }
    }
    // setCursorStateHidden
    void PhysicalWindow::setCursorStateHidden() {
      if (_handle) {
        glfwSetInputMode(handle(_handle), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
      }
    }
    // setCursorStateCaptured
    void PhysicalWindow::setCursorStateCaptured() {
      if (_handle) {
        glfwSetInputMode(handle(_handle), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      }
    }
    // getCursorCoords
    Vec2<> PhysicalWindow::getCursorCoords() const {
      double x, y;
      glfwGetCursorPos(handle(_handle), &x, &y);
      return { DefaultFloat(x), DefaultFloat(y) }; //! narrowing cast
    }

    // pollEvents
    List<WindowEvent> PhysicalWindow::pollEvents() {
      glfwPollEvents();
      return std::exchange(s_event_queues.at(handle(_handle)), {});
    }
    // swapBuffers
    void PhysicalWindow::swapBuffers() {
      glfwSwapBuffers(handle(_handle));
    }

    // bind
    void PhysicalWindow::bind() {
      if (_handle) {
        glfwMakeContextCurrent(handle(_handle));
      }
    }
    // unbind
    void PhysicalWindow::unbind() {
      glfwMakeContextCurrent(nullptr);
    }
  }
}