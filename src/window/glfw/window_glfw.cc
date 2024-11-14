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
        glfwMakeContextCurrent(handle(_handle));
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
}