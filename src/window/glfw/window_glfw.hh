#pragma once
#include "common.hh"

namespace Parrot {
    // WindowGLFW
    class WindowGLFW {
    public:
        // WindowGLFW
        WindowGLFW() = default;
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
    private:
        void* _handle = nullptr;
    };
}