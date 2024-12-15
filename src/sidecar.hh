#pragma once
#include "uuid.hh"

namespace Parrot {
	// extractResourcePath
	stdf::path extractResourcePath(const stdf::path& filepath);

	// Sidecar
	template<class T>
	class Sidecar : public UUIDObject {
	public:
		// Sidecar
		Sidecar(const stdf::path& filepath)
			: UUIDObject(filepath), path(extractResourcePath(filepath)), value(path) {}
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Sidecar(const JSON& json, const stdf::path& filepath)
			: path(filepath.parent_path() / string(json.at("resource"))), value(path) {}

		// path, value
		stdf::path path;
		T value;
	};
}