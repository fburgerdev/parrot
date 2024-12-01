#include "common.hh"
#include "event.hh"

namespace Parrot {
	// getWindowCloseRequest
	WindowCloseRequest* Event::getWindowCloseRequest() {
		if (std::holds_alternative<WindowCloseRequest>(_value)) {
			return &std::get<WindowCloseRequest>(_value);
		}
		return nullptr;
	}
	const WindowCloseRequest* Event::getWindowCloseRequest() const {
		if (std::holds_alternative<WindowCloseRequest>(_value)) {
			return &std::get<WindowCloseRequest>(_value);
		}
		return nullptr;
	}
	// getKeyPress
	KeyPress* Event::getKeyPress() {
		if (std::holds_alternative<KeyPress>(_value)) {
			return &std::get<KeyPress>(_value);
		}
		return nullptr;
	}
	const KeyPress* Event::getKeyPress() const {
		if (std::holds_alternative<KeyPress>(_value)) {
			return &std::get<KeyPress>(_value);
		}
		return nullptr;
	}
	// getMousePress
	MousePress* Event::getMousePress() {
		if (std::holds_alternative<MousePress>(_value)) {
			return &std::get<MousePress>(_value);
		}
		return nullptr;
	}
	const MousePress* Event::getMousePress() const {
		if (std::holds_alternative<MousePress>(_value)) {
			return &std::get<MousePress>(_value);
		}
		return nullptr;
	}
	// getMouseMove
	MouseMove* Event::getMouseMove() {
		if (std::holds_alternative<MouseMove>(_value)) {
			return &std::get<MouseMove>(_value);
		}
		return nullptr;

	}
	const MouseMove* Event::getMouseMove() const {
		if (std::holds_alternative<MouseMove>(_value)) {
			return &std::get<MouseMove>(_value);
		}
		return nullptr;
	}

	// <<
	ostream& operator<<(ostream& stream, const WindowCloseRequest& e) {
		return stream << "WindowCloseRequest()";
	}
	ostream& operator<<(ostream& stream, const KeyPress& e) {
		return stream << "KeyPress(action=" << (int)e.code << ",state=" << (int)e.state << ')';
	}
	ostream& operator<<(ostream& stream, const MousePress& e) {
		return stream << "MousePress(action=" << (int)e.button << ",state=" << (int)e.state << ')';
	}
	ostream& operator<<(ostream& stream, const MouseMove& e) {
		return stream << "MouseMove(x=" << (int)e.delta.x << ",y=" << (int)e.delta.y << ')';
	}
	ostream& operator<<(ostream& stream, const Event& e) {
		if (std::holds_alternative<WindowCloseRequest>(e._value)) {
			return stream << std::get<WindowCloseRequest>(e._value);
		}
		else if (std::holds_alternative<KeyPress>(e._value)) {
			return stream << std::get<KeyPress>(e._value);
		}
		else if (std::holds_alternative<MousePress>(e._value)) {
			return stream << std::get<MousePress>(e._value);
		}
		else if (std::holds_alternative<MouseMove>(e._value)) {
			return stream << std::get<MouseMove>(e._value);
		}
		else {
			return stream << "InvalidEvent()";
		}
	}
}