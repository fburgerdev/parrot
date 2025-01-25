#include "common.hh"
#include "asset_resource.hh"

namespace Parrot {
	// ControlBlock
	AssetResource::ControlBlock::ControlBlock(bool destroy_if_unviewed)
		: destroy_if_unviewed(destroy_if_unviewed) {}

	// AssetResource
	AssetResource::AssetResource(void* value, bool destroy_if_unviewed, const Func<void()>& destroy)
		: _value(value),
		 _control(new ControlBlock(destroy_if_unviewed)),
		 _destroy(destroy) {}
	AssetResource::AssetResource(AssetResource&& other) noexcept
		: _value(std::exchange(other._value, nullptr)),
		 _control(std::exchange(other._control, nullptr)),
		 _destroy(std::move(other._destroy)) {}
	// =
	AssetResource& AssetResource::operator=(AssetResource&& other) noexcept {
		_value = std::exchange(other._value, nullptr);
		_control = std::exchange(other._control, nullptr);
		_destroy = std::move(other._destroy);
		return *this;
	}
	// ~AssetResource
	AssetResource::~AssetResource() {
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
	void* AssetResource::get() {
		return _value;
	}
	const void* AssetResource::get() const {
		return _value;
	}
}