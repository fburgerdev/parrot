#include "common.hh"
#include "window.hh"

namespace Parrot {
	// Window
	Window::Window(const WindowConfig& config) {
		_title = config.title;
		_width = config.width;
		_height = config.height;
		_physical.open(_width, _height, _title);
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

	// pollEvents
	List<Event> Window::pollEvents() {
		return _physical.pollEvents();
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