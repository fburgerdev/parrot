#pragma once
#include "common.hh"

namespace Parrot {
  // JsonType
  template<class T>
  concept JsonType = requires(T json) {
    { json.at("key") };
  };
  // AssetPath
	struct AssetPath {
		// (constructor)
		AssetPath() = default;
    AssetPath(const stdf::path& filepath)
      : filepath(filepath) {}
		AssetPath(const stdf::path& filepath, strview subpath);
		AssetPath(strview path);

    // splitSubpath
    List<string> splitSubpath() const;
    // applySubpathToJSON
		template<JsonType JSON>
    auto applySubpathToJSON(const JSON& root) const {
      const JSON* value = &root;
      for (const string& token : splitSubpath()) {
        if (std::isalpha(token.front())) {
          value = &value->at(token);
        }
        else {
          value = &value->at(std::stoull(token));
        }
      }
      return *value;
    }
    // <=>
    auto operator<=>(const AssetPath&) const = default;

    // filepath, subpath
		stdf::path filepath;
		string subpath;
	};
}