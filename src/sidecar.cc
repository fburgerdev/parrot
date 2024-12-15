#include "common.hh"
#include "sidecar.hh"
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// extractResourcePath
	stdf::path extractResourcePath(const stdf::path& filepath) {
		json data = json::parse(ifstream(filepath));
		return filepath.parent_path() / stdf::path(string(data.at("resource")));
	}
}