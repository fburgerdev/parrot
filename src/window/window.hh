#pragma once
#include "common.hh"

#if defined(PARROT_GLFW)
#include "glfw/window_glfw.hh"
namespace Parrot {
	using PhysicalWindow = WindowGLFW;
}
#endif

namespace Parrot {
	// Window
	class Window {
	public:
		// Window
		Window(const stdf::path& filepath);

		// open
		void open();
		// close
		void close();
		// isOpen
		bool isOpen() const;

		// update
		void update();
	private:
		string _title;
		uint _width, _height;
		PhysicalWindow _physical;
	};
}