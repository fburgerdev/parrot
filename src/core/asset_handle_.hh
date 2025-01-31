#pragma once
#include "uuid.hh"
#include "asset_path.hh"

namespace Parrot {
  // AssetHandle
  template<class T>
  using AssetHandle = Variant<UUID, stdf::path, T>;

  // parseAssetHandle
  template<class T, JsonType JSON>
  inline AssetHandle<T> parseAssetHandle(const JSON& json, const stdf::path& filepath) {
    if (json.is_number()) {
      return UUID(json);
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
    using ResourceFactory = Func<Pair<void*, Func<void()>>(const stdf::path&)>;
    // ReferenceResolver
    using ReferenceResolver = Func<void(const Variant<UUID, stdf::path>&, const ResourceFactory&, const Func<void(const void*)>&)>;

    // (constructor)
    AssetHandleResolver() = default;
    AssetHandleResolver(const ReferenceResolver& asset_api)
      : _resolver(asset_api) {}

    // useHandle
    template<class T>
    void useHandle(const Func<void(const T&)>& func, const AssetHandle<T>& handle) const {
      if (std::holds_alternative<UUID>(handle)) {
        _resolver(std::get<UUID>(handle), [](const stdf::path& path) {
          T* value = new T(path);
          return Pair<void*, Func<void()>>(value, [=] { delete value; });
        }, [&](const void* value) { func(*reinterpret_cast<const T*>(value)); });
      }
      else if (std::holds_alternative<stdf::path>(handle)) {
        _resolver(std::get<stdf::path>(handle), [](const stdf::path& path) {
          T* value = new T(path);
          return Pair<void*, Func<void()>>(value, [=] { delete value; });
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