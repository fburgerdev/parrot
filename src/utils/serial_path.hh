#pragma once
#include "serial_node.hh"

namespace Parrot {
  struct SerialPath {
    SerialPath() = default;
    SerialPath(const stdf::path& filepath);
    SerialPath(const stdf::path& filepath, strview subpath);
    SerialPath(strview path);

    List<string> splitSubpath() const;
    SerialNode applySubpathToNode(const SerialNode& root) const;
    auto operator<=>(const SerialPath& other) const = default;
    friend ostream& operator<<(ostream& stream, const SerialPath& serial_path);

    stdf::path file;
    string sub;
  };
}