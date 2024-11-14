#pragma once
#include "common.hh"

namespace Parrot {
	// AssetManager
	class AssetManager {
	public:
		// AssetManager
		AssetManager(const stdf::path& asset_dir);
		
		// getAsset
		template<class T>
		T& getAsset(const stdf::path& filepath) {
			stdf::path canonical_path = stdf::canonical(_asset_dir / filepath);
			if (!_cache.contains(canonical_path)) {
				_cache.emplace(canonical_path, new T(canonical_path));
			}
			return *(reinterpret_cast<T*>(_cache.at(canonical_path)));
		}
		//TODO:
		// window
		// scene
		// prefab
		// mesh
		// material
		// script
		// texture
		// image
		// shader
	private:
		stdf::path _asset_dir;
		Map<stdf::path, void*> _cache;
	};
}