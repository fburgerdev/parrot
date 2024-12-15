#pragma once
#include "handle.hh"
#include "sidecar.hh"

namespace Parrot {
	// Shader
	struct Shader {
		// Shader
		Shader(const stdf::path& filepath);

		// source
		string source;
	};

	// ShaderProgram
	class ShaderProgram : public UUIDObject {
	public:
		// Shader
		ShaderProgram(const stdf::path& filepath);
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		ShaderProgram(const JSON& json, const stdf::path& filepath) {
			loadFromJSON(json, filepath);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json, const stdf::path& filepath) {
			vertex = parseHandleFromJSON<Sidecar<Shader>>(json.at("vertex"), filepath);
			fragment = parseHandleFromJSON<Sidecar<Shader>>(json.at("fragment"), filepath);
		}

		// vertex, fragment
		Handle<Sidecar<Shader>> vertex, fragment;
	};
}