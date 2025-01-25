#pragma once
#include "common.hh"

namespace Parrot {
	// AssetResource
	class AssetResource {
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
		
		// AssetResource
		template<class T>
		AssetResource(T* value, bool destroy_if_unviewed)
			: _value(value),
			  _control(new ControlBlock(destroy_if_unviewed)),
			  _destroy([=] { delete value; }) {}
		AssetResource(void* value, bool destroy_if_unviewed, const Func<void()>& destroy);
		AssetResource(const AssetResource&) = delete;
		AssetResource(AssetResource&& other) noexcept;
		// =
		AssetResource& operator=(const AssetResource&) = delete;
		AssetResource& operator=(AssetResource&& other) noexcept;
		// ~AssetResource
		~AssetResource();
		
		// get
		void* get();
		const void* get() const;

		// friend
		template<class T>
		friend class AssetView;
	private:
		void* _value;
		ControlBlock* _control;
		Func<void()> _destroy;
	};
	// makeAsset
	template<class T>
	AssetResource makeAsset(const stdf::path& filepath, bool destroy_if_unviewed) {
		return AssetResource(new T(filepath), destroy_if_unviewed);
	}
}