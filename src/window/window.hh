#pragma once
#include "uuid.hh"
#include "asset/config/window_config.hh"

#if defined(PARROT_GLFW)
#include "glfw/window_glfw.hh"
namespace Parrot {
	using PhysicalWindow = WindowGLFW;
}
#endif

namespace Parrot {
	// Window
	class Window : public UUIDObject {
	public:
		// Window
		Window(const WindowConfig& config);

		// isOpen
		bool isOpen() const;
		// close
		void close();

		// setIcon
		void setIcon(const Image& image);

		// update
		void update();
		// bind
		void bind();
		// unbind
		void unbind();
	private:
		string _title;
		uint _width = 0, _height = 0;
		PhysicalWindow _physical;
	};
}