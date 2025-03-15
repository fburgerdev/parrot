#pragma once
#include "common.hh"

namespace Parrot {
  // SerialLeaf
  using SerialLeaf = Variant<nullptr_t, bool, int64, uint64, double, string>;
  
  // SerialNode
  class SerialNode {
  public:
    // (static) loadFromJSON
    static SerialNode loadFromJSON(const stdf::path& filepath);

    // (constructor)
    SerialNode() = default;
    SerialNode(SerialLeaf leaf);
    SerialNode(List<SerialNode> list);
    SerialNode(Map<string, SerialNode> map);

    // value
    template<class T>
    T value() const {
      if (holds<SerialLeaf>(_value)) {
        if (holds<nullptr_t>(std::get<SerialLeaf>(_value))) {
          if constexpr (std::is_convertible_v<nullptr_t, T>) {
            return static_cast<T>(std::get<nullptr_t>(std::get<SerialLeaf>(_value)));
          }
        }
        else if (holds<bool>(std::get<SerialLeaf>(_value))) {
          if constexpr (std::is_convertible_v<bool, T>) {
            return static_cast<T>(std::get<bool>(std::get<SerialLeaf>(_value)));
          }
        }
        else if (holds<int64>(std::get<SerialLeaf>(_value))) {
          if constexpr (std::is_convertible_v<int64, T>) {
            return static_cast<T>(std::get<int64>(std::get<SerialLeaf>(_value)));
          }
        }
        else if (holds<uint64>(std::get<SerialLeaf>(_value))) {
          if constexpr (std::is_convertible_v<uint64, T>) {
            return static_cast<T>(std::get<uint64>(std::get<SerialLeaf>(_value)));
          }
        }
        else if (holds<double>(std::get<SerialLeaf>(_value))) {
          if constexpr (std::is_convertible_v<double, T>) {
            return static_cast<T>((std::get<double>(std::get<SerialLeaf>(_value))));
          }
        }
        else if (holds<string>(std::get<SerialLeaf>(_value))) {
          if constexpr (std::is_convertible_v<string, T>) {
            return static_cast<T>(std::get<string>(std::get<SerialLeaf>(_value)));
          }
        }
      }
      else if (holds<List<SerialNode>>(_value)) {
        if constexpr (std::is_convertible_v<List<SerialNode>, T>) {
          return static_cast<T>(std::get<List<SerialNode>>(_value));
        }
      }
      else if (holds<Map<string, SerialNode>>(_value)) {
        if constexpr (std::is_convertible_v<Map<string, SerialNode>, T>) {
          return static_cast<T>(std::get<Map<string, SerialNode>>(_value));
        }
      }
    }

    // operator()
    template<class T>
    explicit operator T() const {
      return value<T>();
    }

    // is
    bool isNull() const;
    bool isBool() const;
    bool isNumber() const;
    bool isInt() const;
    bool isUint() const;
    bool isFloat() const;
    bool isString() const;
    bool isList() const;
    bool isMap() const;

    // map / list
    // :: size
    usize size() const;

    // map
    // :: contains
    bool contains(const string& key) const;
    // :: at
    SerialNode& at(const string& key);
    const SerialNode& at(const string& key) const;
    // :: operator[]
    SerialNode& operator[](const string& key);
    // :: items
    Map<string, SerialNode>& items();
    const Map<string, SerialNode>& items() const;

    // list
    // :: at
    SerialNode& at(usize index);
    const SerialNode& at(usize index) const;
    // :: operator[]
    SerialNode& operator[](usize index);
    const SerialNode& operator[](usize index) const;
    // :: iterate
    List<SerialNode>::iterator begin();
    List<SerialNode>::const_iterator begin() const;
    List<SerialNode>::iterator end();
    List<SerialNode>::const_iterator end() const;

    // compare
    auto operator==(strview str) const {
      return isString() && value<strview>() == str;
    }
  private:
    Variant<
      Map<string, SerialNode>, List<SerialNode>, SerialLeaf
    > _value = SerialLeaf(nullptr);
  };
}