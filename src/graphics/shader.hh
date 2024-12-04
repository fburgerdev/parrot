#pragma once
#include "handle.hh"
#include "resource.hh"

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
		ShaderProgram(const JSON& json) {
			loadFromJSON(json);
		}

		// loadFromJSON
		template<class JSON> requires(requires(JSON json) { json.at("key"); })
		void loadFromJSON(const JSON& json) {
			vertex = parseHandleFromJSON<Resource<Shader>>(json.at("vertex"));
			fragment = parseHandleFromJSON<Resource<Shader>>(json.at("fragment"));
		}

		// vertex, fragment
		Handle<Resource<Shader>> vertex, fragment;
	};
}