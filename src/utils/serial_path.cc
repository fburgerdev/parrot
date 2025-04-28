#include "common.hh"
#include "serial_path.hh"

namespace Parrot {
  // (constructor)
  SerialPath::SerialPath(const stdf::path& filepath)
    : file(filepath) {}
  SerialPath::SerialPath(const stdf::path& filepath, strview subpath)
    : file(filepath), sub(subpath) {}
  SerialPath::SerialPath(strview path) {
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
  List<string> SerialPath::splitSubpath() const {
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
  SerialNode SerialPath::applySubpathToNode(const SerialNode& root) const {
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
  ostream& operator<<(ostream& stream, const SerialPath& serial_path) {
    stream << serial_path.file.string();
    if (!serial_path.sub.empty()) {
      stream << ":" << serial_path.sub;
    }
    return stream;
  }
}