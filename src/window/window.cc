#include "common.hh"
#include "window.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// Window
	Window::Window(const stdf::path& filepath)
		: _width(0), _height(0) {
		if (filepath.string().ends_with(".json")) {
			auto data = json::parse(ifstream(filepath));
			// title
			_title = data.contains("title") ? data.at("title") : "Untitled Window";
			// size
			_width = data.contains("size") ? uint(data.at("size")[0]) : 1080;
			_height = data.contains("size") ? uint(data.at("size")[1]) : 720;
		}
	}
	// open
	void Window::open() {
		_physical.open(_width, _height, _title);
	}
	// close
	void Window::close() {
		_physical.close();
	}
	// isOpen
	bool Window::isOpen() const {
		return _physical.isOpen();
	}
	// update
	void Window::update() {
		_physical.update();
	}
}