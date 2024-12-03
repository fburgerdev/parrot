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

	// pollEvents
	List<Event> Window::pollEvents() {
		List<Event> events = _physical.pollEvents();
		// TODO: make window initialization more robust
		for (Event& e : events) {
			if (auto* wcr = e.getWindowCloseRequest()) {
				wcr->window = this;
			}
			else if (auto* kp = e.getKeyPress()) {
				kp->window = this;
			}
			else if (auto* mp = e.getMousePress()) {
				mp->window = this;
			}
			else if (auto* mm = e.getMouseMove()) {
				mm->window = this;
			}
			else {
				throw std::logic_error("unexpected branch");
			}
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