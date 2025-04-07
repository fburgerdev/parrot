#include "common.hh"
#include "serial_node.hh"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (static) json
  // :: createFromJSON
  static SerialNode createFromJSON(const json& json) {
    if (json.is_primitive()) {
      if (json.is_null()) {
        return { SerialLeaf(null()) };
      }
      else if (json.is_boolean()) {
        return { SerialLeaf(bool(json)) };
      }
      else if (json.is_number()) {
        if (json.is_number_float()) {
          return { SerialLeaf(double(json)) };
        }
        else if (json.is_number_unsigned()) {
          return { SerialLeaf(uint64(json)) };
        }
        else {
          return { SerialLeaf(int64(json)) };
        }
      }
      else if (json.is_string()) {
        return { SerialLeaf(string(json)) };
      }
    }
    else if (json.is_array()) {
      List<SerialNode> list;
      for (const auto& value : json) {
        list.emplace_back(createFromJSON(value));
      }
      return { list };
    }
    else if (json.is_object()) {
      Map<string, SerialNode> map;
      for (const auto& [key, value] : json.items()) {
        map.emplace(key, createFromJSON(value));
      }
      return { map };
    }
  }
  // :: loadFromJSON
  SerialNode SerialNode::loadFromJSON(strview source) {
    try {
      auto json = json::parse(source);
      return createFromJSON(json);
    }
    catch (const std::exception& e) {
      throw;
    }
  }
  SerialNode SerialNode::loadFromJSON(const stdf::path& filepath) {
    try {
      auto json = json::parse(ifstream(filepath));
      return createFromJSON(json);
    }
    catch (const std::exception& e) {
      throw;
    }
  }

  // (constructor)
  SerialNode::SerialNode(SerialLeaf leaf)
    : _value(std::move(leaf)) {}
  SerialNode::SerialNode(List<SerialNode> list)
    : _value(std::move(list)) {}
  SerialNode::SerialNode(Map<string, SerialNode> map)
    : _value(std::move(map)) {}

  // is
  bool SerialNode::isNull() const {
    if (holds<SerialLeaf>(_value)) {
      return holds<null>(std::get<SerialLeaf>(_value));
    }
    return false;
  }
  bool SerialNode::isBool() const {
    if (holds<SerialLeaf>(_value)) {
      return holds<bool>(std::get<SerialLeaf>(_value));
    }
    return false;
  }
  bool SerialNode::isNumber() const {
    return isInt() || isUint() || isFloat();
  }
  bool SerialNode::isInt() const {
    if (holds<SerialLeaf>(_value)) {
      return holds<int64>(std::get<SerialLeaf>(_value));
    }
    return false;
  }
  bool SerialNode::isUint() const {
    if (holds<SerialLeaf>(_value)) {
      return holds<uint64>(std::get<SerialLeaf>(_value));
    }
    return false;
  }
  bool SerialNode::isFloat() const {
    if (holds<SerialLeaf>(_value)) {
      return holds<double>(std::get<SerialLeaf>(_value));
    }
    return false;
  }
  bool SerialNode::isString() const {
    if (holds<SerialLeaf>(_value)) {
      return holds<string>(std::get<SerialLeaf>(_value));
    }
    return false;
  }
  bool SerialNode::isList() const {
    return holds<List<SerialNode>>(_value);
  }
  bool SerialNode::isMap() const {
    return holds<Map<string, SerialNode>>(_value);
  }

  // map / list
  // :: size
  usize SerialNode::size() const {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).size();
    }
    else if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value).size();
    }
  }

  // map
  // :: contains
  bool SerialNode::contains(const string& key) const {
    if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value).contains(key);
    }
  }
  // :: at
  SerialNode& SerialNode::at(const string& key) {
    if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value).at(key);
    }
  }
  const SerialNode& SerialNode::at(const string& key) const {
    if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value).at(key);
    }
  }
  // :: operator[]
  SerialNode& SerialNode::operator[](const string& key) {
    if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value)[key];
    }
  }
  // :: items
  Map<string, SerialNode>& SerialNode::items() {
    if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value);
    }
  }
  const Map<string, SerialNode>& SerialNode::items() const {
    if (holds<Map<string, SerialNode>>(_value)) {
      return std::get<Map<string, SerialNode>>(_value);
    }
  }

  // map
  // :: at
  SerialNode& SerialNode::at(usize index) {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).at(index);
    }
  }
  const SerialNode& SerialNode::at(usize index) const {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).at(index);
    }
  }
  // :: operator[]
  SerialNode& SerialNode::operator[](usize index) {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value)[index];
    }
  }
  const SerialNode& SerialNode::operator[](usize index) const {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value)[index];
    }
  }
  // :: iterate
  List<SerialNode>::iterator SerialNode::begin() {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).begin();
    }
  }
  List<SerialNode>::const_iterator SerialNode::begin() const {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).begin();
    }
  }
  List<SerialNode>::iterator SerialNode::end() {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).end();
    }
  }
  List<SerialNode>::const_iterator SerialNode::end() const {
    if (holds<List<SerialNode>>(_value)) {
      return std::get<List<SerialNode>>(_value).end();
    }
  }

  // << (stream)
  ostream& operator<<(ostream& stream, const SerialNode& node) {
    return stream << "SERIALNODE"; //TODO: properly print serial-node
  }
}