#include "common.hh"
#include "asset_path.hh"

namespace Parrot {
  // (constructor)
  AssetPath::AssetPath(const stdf::path& filepath, strview subpath)
    : file(filepath), sub(subpath) {}
  AssetPath::AssetPath(strview path) {
    usize index = path.find(':');
    if (index == string::npos) {
      file = stdf::path(path);
    }
    else {
      file = stdf::path(path.substr(0, index));
      sub = string(path.substr(index + 1));
    }
  }
  // splitSubpath
  List<string> AssetPath::splitSubpath() const {
    List<string> splitted = { "" };
    for (char ch : sub) {
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