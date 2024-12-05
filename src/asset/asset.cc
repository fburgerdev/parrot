#include "common.hh"
#include "asset.hh"

namespace Parrot {
	// ControlBlock
	Asset::ControlBlock::ControlBlock(bool destroy_if_unviewed)
		: destroy_if_unviewed(destroy_if_unviewed) {}

	// Asset
	Asset::Asset(void* value, bool destroy_if_unviewed, const function<void()>& destroy)
		: _value(value),
		 _control(new ControlBlock(destroy_if_unviewed)),
		 _destroy(destroy) {}
	Asset::Asset(Asset&& other) noexcept
		: _value(std::exchange(other._value, nullptr)),
		 _control(std::exchange(other._control, nullptr)),
		 _destroy(std::move(other._destroy)) {}
	// =
	Asset& Asset::operator=(Asset&& other) noexcept {
		_value = std::exchange(other._value, nullptr);
		_control = std::exchange(other._control, nullptr);
		_destroy = std::move(other._destroy);
		return *this;
	}
	// ~Asset
	Asset::~Asset() {
		if (_control) {
			if (_control->ref_count == 1) {
				delete _control;
			}
			else {
				_control->is_valid = false;
				--(_control->ref_count);
			}
			_destroy();
		}
	}
	// get
	void* Asset::get() {
		return _value;
	}
	const void* Asset::get() const {
		return _value;
	}
}