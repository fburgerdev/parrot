#include "common.hh"
#include "shader.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// Shader
	Shader::Shader(const stdf::path& filepath)
		: source((strstream() << ifstream(filepath).rdbuf()).str()) {}

	// ShaderProgram
	ShaderProgram::ShaderProgram(const stdf::path& filepath) {
		loadFromJSON(json::parse(ifstream(filepath)));
	}
}