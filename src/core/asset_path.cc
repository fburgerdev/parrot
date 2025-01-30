#include "common.hh"
#include "asset_path.hh"

namespace Parrot {
  // (constructor)
  AssetPath::AssetPath(const stdf::path& filepath, strview subpath)
    : filepath(filepath), subpath(subpath) {}
  AssetPath::AssetPath(strview path) {
    usize index = path.find(':');
    if (index == string::npos) {
      filepath = stdf::path(path);
    }
    else {
      filepath = stdf::path(path.substr(0, index));
      subpath = string(path.substr(index + 1));
    }
  }
  // splitSubpath
  List<string> AssetPath::splitSubpath() const {
    List<string> splitted = { "" };
    for (char ch : subpath) {
      if (ch == '.' || ch == '[' || ch == ']') {
        if (!splitted.back().empty()) {
          splitted.emplace_back();
        }
      }
      else {
        splitted.back().push_back(ch);
      }
    }
    if (splitted.back().empty()) {
      splitted.pop_back();
    }
    return splitted;
  }
}