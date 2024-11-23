#pragma once
#include "common.hh"

namespace Parrot {
    // WindowGLFW
    class WindowGLFW {
    public:
        // WindowGLFW
        WindowGLFW() = default;
        WindowGLFW(const WindowGLFW&) = delete;
        WindowGLFW(WindowGLFW&& other);
        // =
        WindowGLFW& operator=(const WindowGLFW&) = delete;
        WindowGLFW& operator=(WindowGLFW&& other);
        // ~WindowGLFW
        ~WindowGLFW();
        
        // open
        bool open(uint width, uint height, strview title);
        // close
        void close();
        // isOpen
        bool isOpen() const;

        // update
        void update();
        // bind
        void bind();
        // unbind
        void unbind();
    private:
        void* _handle = nullptr;
    };
}