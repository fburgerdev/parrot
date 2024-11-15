#pragma once
#include "common.hh"

namespace Parrot {
	// Asset
	class Asset {
	public:
		// ControlBlock
		struct ControlBlock {
			// ControlBlock
			ControlBlock(bool destroy_if_unviewed)
				: destroy_if_unviewed(destroy_if_unviewed) {}

			// destroy_if_unviewed, is_valid, ref_count
			bool destroy_if_unviewed;
			bool is_valid = true;
			usize ref_count = 1;
		};
		
		// Asset
		template<class T>
		Asset(T* value, bool destroy_if_unviewed)
			: _value(value),
			  _control(new ControlBlock(destroy_if_unviewed)),
			  _destroy([=] { delete value; }) {}
		Asset(const Asset&) = delete;
		Asset(Asset&& other) noexcept
			: _value(std::exchange(other._value, nullptr)),
			  _control(std::exchange(other._control, nullptr)),
			  _destroy(std::move(other._destroy)) {}
		// =
		Asset& operator=(const Asset&) = delete;
		Asset& operator=(Asset&& other) noexcept {
			_value = std::exchange(other._value, nullptr);
			_control = std::exchange(other._control, nullptr);
			_destroy = std::move(other._destroy);
			return *this;
		}
		// ~Asset
		~Asset() {
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
		
		// friend
		template<class T>
		friend class AssetView;
	private:
		void* _value;
		ControlBlock* _control;
		function<void()> _destroy;
	};
	// makeAsset
	template<class T>
	Asset makeAsset(const stdf::path& filepath, bool destroy_if_unviewed) {
		return Asset(new T(filepath), destroy_if_unviewed);
	}
}