#include "common.hh"
#include "window_glfw.hh"
#include "debug/debug.hh"
#include <glad/glad.hh>
#include <glfw/glfw3.hh>

namespace Parrot {
    // HandleGLFW
    using HandleGLFW = GLFWwindow;
    
    // (static) event_queues
    static Map<HandleGLFW*, List<Event>> s_event_queues;

    // (static) handle
    static HandleGLFW* handle(void* ptr) {
        return reinterpret_cast<HandleGLFW*>(ptr);
    }

    // WindowGLFW
    WindowGLFW::WindowGLFW(WindowGLFW&& other) noexcept
        : _handle(std::exchange(other._handle, nullptr)) {}
    // =
    WindowGLFW& WindowGLFW::operator=(WindowGLFW&& other) noexcept {
        _handle = std::exchange(other._handle, nullptr);
        return *this;
    }
    // ~WindowGLFW
    WindowGLFW::~WindowGLFW() {
        close();
    }

    // open
    bool WindowGLFW::open(uint width, uint height, strview title) {
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
        _handle = glfwCreateWindow(width, height, string(title).c_str(), NULL, NULL);
        if (!_handle) {
            glfwTerminate();
            return false;
        }
        s_event_queues.emplace(handle(_handle), List<Event>());
        bind();
        glfwSwapInterval(1);

        // add callbacks
        glfwSetWindowCloseCallback(handle(_handle), [](HandleGLFW* window) {
            Event e(WindowCloseRequest({}));
            s_event_queues.at(window).push_back(e);
            LOG_WINDOW_TRACE("detected {}", e);
        });
        glfwSetMouseButtonCallback(handle(_handle), [](HandleGLFW* window, int glfw_button, int glfw_action, int glfw_mods) {
            MouseButton button = (
                glfw_button == GLFW_MOUSE_BUTTON_LEFT ? MouseButton::LEFT : (
                    glfw_button == GLFW_MOUSE_BUTTON_MIDDLE ? MouseButton::MIDDLE : (
                        glfw_button == GLFW_MOUSE_BUTTON_RIGHT ? MouseButton::RIGHT : throw
                    )
                )
            );
            MouseState state = (
                glfw_action == GLFW_PRESS ? MouseState::PRESSED : (
                    glfw_action == GLFW_RELEASE ? MouseState::RELEASED : throw
                )
            );
            Event e(MousePress({ button, state }));
            s_event_queues.at(window).push_back(e);
            LOG_WINDOW_TRACE("detected {}", e);
        });
        glfwSetKeyCallback(handle(_handle), [](HandleGLFW* window, int glfw_key, int glfw_scancode, int glfw_action, int glfw_mods) {
            KeyCode code = (KeyCode)glfw_key;
            KeyState state = (
                glfw_action == GLFW_PRESS ? KeyState::PRESSED : (
                    glfw_action == GLFW_RELEASE ? KeyState::RELEASED : (
                        glfw_action == GLFW_REPEAT ? KeyState::REPEATED : throw
                    )
                )
            );
            Event e(KeyPress({ code, state }));
            s_event_queues.at(window).push_back(e);
            LOG_WINDOW_TRACE("detected {}", e);
        });
        glfwSetCursorPosCallback(handle(_handle), [](HandleGLFW* window, double glfw_x, double glfw_y) {
            Event e(MouseMove({ Vec2<float32>(float32(glfw_x), float32(glfw_y)) }));
            s_event_queues.at(window).push_back(e);
            LOG_WINDOW_TRACE("detected {}", e);
        });

        // init glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return false;
        }

        return true;
    }
    // close
    void WindowGLFW::close() {
        if (isOpen()) {
            glfwDestroyWindow(handle(_handle));
            s_event_queues.erase(handle(_handle));
            _handle = nullptr;
        }
    }
    // isOpen
    bool WindowGLFW::isOpen() const {
        return _handle;
    }

    // setIcon
    void WindowGLFW::setIcon(const Image& image) {
        GLFWimage images[1];
        images[0].width = image.getWidth();
        images[0].height = image.getHeight();
        images[0].pixels = (uchar*)image.getBytes(); //! unsafe if glfw modifies bytes
        glfwSetWindowIcon(handle(_handle), 1, images);
    }

    // pollEvents
    List<Event> WindowGLFW::pollEvents() {
        glfwPollEvents();
        return std::exchange(s_event_queues.at(handle(_handle)), {});
    }
    // swapBuffers
    void WindowGLFW::swapBuffers() {
        glfwSwapBuffers(handle(_handle));
    }
    
    // (static) bound
    static Stack<WindowGLFW*> s_bound;
    // bind
    void WindowGLFW::bind() {
        s_bound.push(this);
        glfwMakeContextCurrent(handle(_handle));
    }
    // unbind
    void WindowGLFW::unbind() {
        s_bound.pop();
        if (s_bound.empty()) {
            glfwMakeContextCurrent(nullptr);
        }
        else {
            glfwMakeContextCurrent(handle(s_bound.top()->_handle));
        }
    }
}