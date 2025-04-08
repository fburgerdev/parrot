#include "common.hh"
#include "asset_path.hh"

namespace Parrot {
  // (constructor)
  AssetPath::AssetPath(const stdf::path& file)
    : file(file) {}
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
  // applySubpathToNode
  SerialNode AssetPath::applySubpathToNode(const SerialNode& root) const {
    const SerialNode* value = &root;
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
  // << (stream)
  ostream& operator<<(ostream& stream, const AssetPath& asset_path) {
    if (asset_path.debug_root) {
      auto rel_path = stdf::relative(asset_path.file, *asset_path.debug_root);
      stream << rel_path.string();
    }
    else {
      stream << asset_path.file.string();
    }
    if (!asset_path.sub.empty()) {
      stream << ":" << asset_path.sub;
    }
    return stream;
  }
}