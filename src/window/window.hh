#pragma once
#include "uuid.hh"
#include "window_config.hh"
#include "window_event.hh"

#if defined(PARROT_GLFW)
#include "glfw/physical_window_glfw.hh"
namespace Parrot {
	using PhysicalWindow = GLFW::PhysicalWindow;
}
#endif

namespace Parrot {
	// Window
	class Window : public UUIDObject, public Scriptable {
	public:
		// Window / ~Window
		Window(const WindowConfig& config, Scriptable* parent = nullptr);
		Window(Window&&) = default;
		~Window();
		// =
		Window& operator=(Window&&) = default;

		// getTitle
		const string& getTitle();

		// isOpen
		bool isOpen() const;
		// close
		void close();

		// setIcon
		void setIcon(const Image& image);
		// setCursorState
		void setCursorState(CursorState state);

		// foreachChild (scriptable)
		virtual void foreachChild(function<void(Scriptable&)> func) override;
		virtual void foreachChild(function<void(const Scriptable&)> func) const override;

		// pollEvents
		List<WindowEvent> pollEvents();
		// swapBuffers
		void swapBuffers();
		// bind
		void bind();
		// unbind
		void unbind();
	private:
		string _title;
		uint _width = 0, _height = 0;
		CursorState _cursor = CursorState::NORMAL;
		PhysicalWindow _physical;
	};
}