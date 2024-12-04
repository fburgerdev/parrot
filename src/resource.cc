#include "common.hh"
#include "resource.hh"
#include "nlohmann/json.hh"
using json = nlohmann::json;

namespace Parrot {
	// extractResourcePath
	stdf::path extractResourcePath(const stdf::path& filepath) {
		json data = json::parse(ifstream(filepath));
		return filepath / stdf::path(string(data.at("resource")));
	}
}