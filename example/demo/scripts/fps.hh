#pragma once
#include "client.hh"

namespace Parrot {
	// FPS
	class FPS : public WindowScript {
	public:
		// FPS
		FPS(Window& window)
			: WindowScript(window) {}
		
		// onAttach / onDetach
		virtual void onAttach() override {
			_captured = true;
			window->setCursorState(CursorState::CAPTURED);
		}
		virtual void onDetach() override {
			_captured = false;
			window->setCursorState(CursorState::NORMAL);
		}
		// resolveEvent
		virtual bool resolveEvent(const Event& e) override {
			if (auto* kp = e.getKeyPress()) {
				if (kp->state == KeyState::PRESSED) {
					if (kp->code == KeyCode::KEY_ESCAPE) {
						if (_captured) {
							_captured = false;
							window->setCursorState(CursorState::NORMAL);
						}
						else {
							window->close();
						}
						return true;
					}
				}
			}
			else if (auto* mp = e.getMousePress()) {
				if (mp->state == MouseState::PRESSED) {
					if (mp->button == MouseButton::LEFT) {
						if (!_captured) {
							_captured = true;
							window->setCursorState(CursorState::CAPTURED);
							return true;
						}
					}
				}
			}
			return false;
		}
	private:
		bool _captured = false;
	};
}