#include "common.hh"
#include "window.hh"
#include "registry.hh"

namespace Parrot {
	// Window / ~Window
	Window::Window(const WindowConfig& config, Scriptable* parent)
		: Scriptable(parent) {
		_title = config.title;
		_width = config.width;
		_height = config.height;
		_physical.open(_width, _height, _title);
		setCursorState(config.cursor);
		for (const string& script_name : config.scripts) {
			auto [id, factory] = g_registry<Script, Window&>.at(script_name);
			addScript(id, factory(*this));
		}
	}
	Window::~Window() {
		Scriptable::removeAllScripts();
	}

	// getTitle
	const string& Window::getTitle() {
		return _title;
	}

	// isOpen
	bool Window::isOpen() const {
		return _physical.isOpen();
	}
	// close
	void Window::close() {
		_physical.close();
	}

	// setIcon
	void Window::setIcon(const Image& image) {
		_physical.setIcon(image);
	}
	// setCursorState
	void Window::setCursorState(CursorState state) {
		if (state != _cursor) {
			switch (state) {
			case Parrot::CursorState::NORMAL:
				_physical.setCursorStateNormal();
				break;
			case Parrot::CursorState::HIDDEN:
				_physical.setCursorStateHidden();
				break;
			case Parrot::CursorState::CAPTURED:
				_physical.setCursorStateCaptured();
				break;
			default:
				break;
			}
			_cursor = state;
		}
	}

	// foreachChild (scriptable)
	void Window::foreachChild([[maybe_unused]] function<void(Scriptable&)> func) {
		// do nothing
	}
	void Window::foreachChild([[maybe_unused]] function<void(const Scriptable&)> func) const {
		// do nothing
	}

	// pollEvents
	List<WindowEvent> Window::pollEvents() {
		List<WindowEvent> events = _physical.pollEvents();
		for (WindowEvent& e : events) {
			e.target = this;
		}
		return events;
	}
	// swapBuffers
	void Window::swapBuffers() {
		_physical.swapBuffers();
	}
	// bind
	void Window::bind() {
		_physical.bind();
	}
	// unbind
	void Window::unbind() {
		_physical.unbind();
	}
}