#pragma once
#include "handle.hh"
#include "sidecar.hh"

namespace Parrot {
	// ShaderStage
	struct ShaderStage {
		// ShaderStage
		ShaderStage(const stdf::path& filepath);

		// source
		string source;
	};

	// ShaderSource
	class ShaderSource : public UUIDObject {
	public:
		// ShaderStage
		ShaderSource(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		ShaderSource(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, const stdf::path& filepath) {
			vertex = parseHandleFromJSON<Sidecar<ShaderStage>>(json.at("vertex"), filepath);
			fragment = parseHandleFromJSON<Sidecar<ShaderStage>>(json.at("fragment"), filepath);
		}

		// vertex, fragment
		Handle<Sidecar<ShaderStage>> vertex, fragment;
	};
}