#include "common.hh"
#include "window_glfw.hh"
#include <glad/glad.hh>
#include <glfw/glfw3.hh>

namespace Parrot {
    // HandleGLFW
    using HandleGLFW = GLFWwindow;
    // handle
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
        bind();
        glfwSwapInterval(1);

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

    // update
    void WindowGLFW::update() {
        glfwSwapBuffers(handle(_handle));
        glfwPollEvents();
    }
    
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