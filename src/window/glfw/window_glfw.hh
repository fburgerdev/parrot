#pragma once
#include "utils/image.hh"

namespace Parrot {
    // WindowGLFW
    class WindowGLFW {
    public:
        // WindowGLFW
        WindowGLFW() = default;
        WindowGLFW(const WindowGLFW&) = delete;
        WindowGLFW(WindowGLFW&& other) noexcept;
        // =
        WindowGLFW& operator=(const WindowGLFW&) = delete;
        WindowGLFW& operator=(WindowGLFW&& other) noexcept;
        // ~WindowGLFW
        ~WindowGLFW();
        
        // open
        bool open(uint width, uint height, strview title);
        // close
        void close();
        // isOpen
        bool isOpen() const;

        // setIcon
        void setIcon(const Image& image);

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