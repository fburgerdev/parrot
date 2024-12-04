#pragma once
#include "shader.hh"

namespace Parrot {
	// Material
	class Material : public UUIDObject {
	public:
		// Material
		Material(const stdf::path& filepath);

		// loadFromJSON
		template<class JSON>
		void loadFromJSON(const JSON& json) {
			shader = parseHandleFromJSON<ShaderProgram>(json.at("shader"));
		}

		// shader
		// TODO: values...
		Handle<ShaderProgram> shader;
	};
}