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