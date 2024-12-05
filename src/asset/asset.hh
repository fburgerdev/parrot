#pragma once
#include "common.hh"

namespace Parrot {
	// Asset
	class Asset {
	public:
		// ControlBlock
		struct ControlBlock {
			// ControlBlock
			ControlBlock(bool destroy_if_unviewed);

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
		Asset(void* value, bool destroy_if_unviewed, const function<void()>& destroy);
		Asset(const Asset&) = delete;
		Asset(Asset&& other) noexcept;
		// =
		Asset& operator=(const Asset&) = delete;
		Asset& operator=(Asset&& other) noexcept;
		// ~Asset
		~Asset();
		
		// get
		void* get();
		const void* get() const;

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