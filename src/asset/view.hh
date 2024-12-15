#pragma once
#include "asset.hh"

namespace Parrot {
	// AssetView
	template<class T>
	class AssetView {
	public:
		// AssetView / ~AssetView
		AssetView() = default;
		AssetView(Asset& asset, function<void()>&& destroy)
			: _value(reinterpret_cast<T*>(asset._value)),
			  _control(asset._control),
			  _destroy(std::move(destroy)) {
			++(_control->ref_count);
		}
		AssetView(const AssetView<T>& other)
			: _value(other._value),
			  _control(other._control),
			  _destroy(other._destroy) {
			if (_control) {
				++(_control->ref_count);
			}
		}
		AssetView(AssetView<T>&& other) noexcept
			: _value(std::exchange(other._value, nullptr)),
			  _control(std::exchange(other._control, nullptr)),
			  _destroy(std::move(other._destroy)) {}
		~AssetView() {
			if (_control) {
				if (_control->is_valid) {
					if (_control->ref_count == 1 ||
						(_control->destroy_if_unviewed && _control->ref_count == 2)) {
						_destroy();
					}
				}
				if (_control->ref_count == 1) {
					delete _control;
				}
				else {
					--(_control->ref_count);
				}
			}
		}
		// =
		AssetView<T>& operator=(const AssetView<T>& other) {
			_value = other._value;
			_control = other._control;
			_destroy = other._destroy;
			if (_control) {
				++(_control->ref_count);
			}
		}
		AssetView<T>& operator=(AssetView<T>&& other) noexcept {
			_value = std::exchange(other._value, nullptr);
			_control = std::exchange(other._control, nullptr);
			_destroy = std::move(other._destroy);
			return *this;
		}

		// *
		T& operator*() {
			return *_value;
		}
		const T& operator*() const {
			return *_value;
		}
		// ->
		T* operator->() {
			return _value;
		}
		const T* operator->() const {
			return _value;
		}
		// get
		T* get() {
			return _value;
		}
		const T* get() const {
			return _value;
		}
	private:
		T* _value;
		Asset::ControlBlock* _control;
		function<void()> _destroy;
	};
}