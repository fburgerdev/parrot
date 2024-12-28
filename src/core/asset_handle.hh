#pragma once
#include "uuid.hh"

namespace Parrot {
	// AssetHandle
	template<class T>
	using AssetHandle = Variant<uuid, stdf::path, T>;

	// parseAssetHandle
	template<class T, class JSON> requires(requires(JSON json) { json.at("key"); })
	inline AssetHandle<T> parseAssetHandle(const JSON& json, const stdf::path& filepath) {
		if (json.is_number()) {
			return uuid(json);
		}
		else if (json.is_string()) {
			return stdf::path(string(json));
		}
		else {
			return T(json, filepath);
		}
	}

	// AssetHandleResolver
	class AssetHandleResolver {
	public:
		// ResourceFactory
		using ResourceFactory = function<Pair<void*, function<void()>>(const stdf::path&)>;
		// ReferenceResolver
		using ReferenceResolver = function<void(const Variant<uuid, stdf::path>&, const ResourceFactory&, const function<void(const void*)>&)>;

		// AssetHandleResolver
		AssetHandleResolver() = default;
		AssetHandleResolver(const ReferenceResolver& resolver)
			: _resolver(resolver) {}

		// useHandle
		template<class T>
		void useHandle(const function<void(const T&)>& func, const AssetHandle<T>& handle) const {
			if (std::holds_alternative<uuid>(handle)) {
				_resolver(std::get<uuid>(handle), [](const stdf::path& path) {
					T* value = new T(path);
					return Pair<void*, function<void()>>(value, [=] { delete value; });
				}, [&](const void* value) { func(*reinterpret_cast<const T*>(value)); });
			}
			else if (std::holds_alternative<stdf::path>(handle)) {
				_resolver(std::get<stdf::path>(handle), [](const stdf::path& path) {
					T* value = new T(path);
					return Pair<void*, function<void()>>(value, [=] { delete value; });
				}, [&](const void* value) { func(*reinterpret_cast<const T*>(value)); });
			}
			else {
				func(std::get<T>(handle));
			}
		}
		// useHandles
		template<class TFirst, class... TRest>
		void useHandles(const auto& func, const AssetHandle<TFirst>& first, const AssetHandle<TRest>&... rest) const {
			useHandle<TFirst>([&](const TFirst& value) {
				if constexpr (sizeof...(TRest) > 0) {
					useHandles([&](const TRest&... rest) {
						func(value, rest...);
					}, rest...);
				}
				else {
					func(value);
				}
			}, first);
		}
	private:
		ReferenceResolver _resolver;
	};
}