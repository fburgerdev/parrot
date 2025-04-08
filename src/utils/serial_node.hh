#pragma once
#include "common.hh"

namespace Parrot {
  // null
  struct null {
    // <=> (compare)
    auto operator<=>(const null& other) const = default;
  };

  // SerialLeaf
  using SerialLeaf = Variant<null, bool, int64, uint64, double, string>;
  
  // SerialNode
  class SerialNode {
  public:
    // (static) loadFromJSON
    static SerialNode loadFromJSON(strview source);
    static SerialNode loadFromJSON(const stdf::path& filepath);

    // SerialList, SerialMap
    using SerialList = List<SerialNode>;
    using SerialMap = Map<string, SerialNode>;

    // (constructor)
    SerialNode() = default;
    SerialNode(SerialLeaf leaf);
    SerialNode(List<SerialNode> list);
    SerialNode(Map<string, SerialNode> map);

    // value
    template<class T>
    T value() const;

    // operator()
    template<class T>
    explicit operator T() const;

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

    // == (compare)
    bool operator==(strview str) const;
    // <=> (compare)
    std::partial_ordering operator<=>(const SerialNode& other) const;
    // << (stream)
    friend ostream& operator<<(ostream& stream, const SerialNode& node);
  private:
    Variant<SerialMap, SerialList, SerialLeaf> _value = SerialLeaf(null());
  };
}
#include "serial_node_impl.hh"