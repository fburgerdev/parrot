#pragma once
#include "common.hh"

namespace Parrot {
	// KeyPress
	// :: Code
	// TODO: KeyCode
	// :: State
	enum class KeyState {
		PRESSED, RELEASED, REPEATED
	};
	// :: Event
	struct KeyPress {
		// code, state
		// KeyCode code;
		KeyState state;
	};

	// MousePress
	// :: Button
	enum class MouseButton {
		LEFT, MIDDLE, RIGHT
	};
	// :: State
	enum class MouseState {
		PRESSED, RELEASED
	};
	// :: Event
	struct MousePress {
		// button, state
		MouseButton button;
		MouseState state;
	};
	
	// Event
	class Event {
	public:
		// getKeyPress
		KeyPress* getKeyPress();
		const KeyPress* getKeyPress() const;
		// getMousePress
		MousePress* getMousePress();
		const MousePress* getMousePress() const;
	private:
		Variant<
			KeyPress, MousePress
		> _value;
	};
}