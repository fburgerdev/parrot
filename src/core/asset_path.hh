#pragma once
#include "utils/uuid.hh"
#include "utils/serial_node.hh"

namespace Parrot {
  // AssetPath
  struct AssetPath {
    // (constructor)
    AssetPath() = default;
    AssetPath(const stdf::path& file);
    AssetPath(const stdf::path& file, strview sub);
    AssetPath(strview path);

    // splitSubpath
    List<string> splitSubpath() const;
    // applySubpathToNode
    SerialNode applySubpathToNode(const SerialNode& root) const;
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
  using AssetKey = Variant<UUID, AssetPath>;
}