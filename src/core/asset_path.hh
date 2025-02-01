#pragma once
#include "uuid.hh"

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
    AssetPath(const stdf::path& file)
      : file(file) {}
    AssetPath(const stdf::path& file, strview sub);
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
    // <=> (compare)
    auto operator<=>(const AssetPath& other) const {
      return std::tie(file, sub) <=> std::tie(other.file, other.sub);
    }

    // file, sub, debug_root
    stdf::path file;
    string sub;
    Opt<stdf::path> debug_root; // for debugging
  };
  // <<
  ostream& operator<<(ostream& stream, const AssetPath& asset_path);
  // AssetKey
  using AssetKey = Variant<UUID, AssetPath>;
}