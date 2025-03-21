#pragma once
#include "utils/uuid.hh"

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
    AssetPath(const stdf::path& file); /* API */
    AssetPath(const stdf::path& file, strview sub) /* API */;
    AssetPath(strview path) /* API */;

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
    // <=> (compare)
    auto operator<=>(const AssetPath& other) const = default;
    // << (stream)
    friend ostream& operator<<(ostream& stream, const AssetPath& asset_path);

    // file, sub, debug_root
    stdf::path file;
    string sub;
    Opt<stdf::path> debug_root; // for debugging
  };
  // AssetKey
  using AssetKey = Variant<UUID, AssetPath>; /* API */
}