#include "common.hh"
#include "event.hh"

namespace Parrot {
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
}