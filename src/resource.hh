#pragma once
#include "uuid.hh"

namespace Parrot {
	// extractResourcePath
	stdf::path extractResourcePath(const stdf::path& filepath);

	// Resource
	template<class T>
	class Resource {
	public:
		// Resource
		Resource(const stdf::path& filepath)
			: path(extractResourcePath(filepath)), value(path) {}
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		Resource(const JSON& json)
			: path(string(json.at("resource"))), value(path) {}

		// path, value
		stdf::path path;
		T value;
	};
}