#include "common.hh"
#include "shader_source.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// ShaderStage
	ShaderStage::ShaderStage(const stdf::path& filepath)
		: source((strstream() << ifstream(filepath).rdbuf()).str()) {}

	// ShaderSource
	ShaderSource::ShaderSource(const stdf::path& filepath)
		: UUIDObject(filepath) {
		loadFromJSON(json::parse(ifstream(filepath)), filepath);
	}
}