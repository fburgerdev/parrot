#pragma once
#include "uuid.hh"

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
		Window(const stdf::path& filepath);

		// isOpen
		bool isOpen() const;

		// update
		void update();
		// bind
		void bind();
		// unbind
		void unbind();

		// getSceneUUID
		uuid getSceneUUID() const;

		// friend
		friend class App;
	private:
		void open();
		void close();

		string _title;
		uint _width, _height;
		PhysicalWindow _physical;
		uuid _scene_uuid = 0;
	};
}