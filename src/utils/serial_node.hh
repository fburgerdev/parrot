#pragma once
#include "common.hh"

namespace Parrot {
  struct null {
    auto operator<=>(const null& other) const = default;
  };

  using SerialLeaf = Variant<null, bool, int64, uint64, double, string>;
  
  class SerialNode {
  public:
    static SerialNode loadFromJSON(strview source);
    static SerialNode loadFromJSON(const stdf::path& filepath);

    using SerialList = List<SerialNode>;
    using SerialMap = Map<string, SerialNode>;

    SerialNode() = default;
    SerialNode(SerialLeaf leaf);
    SerialNode(List<SerialNode> list);
    SerialNode(Map<string, SerialNode> map);

    template<class T>
    T value() const;

    template<class T>
    explicit operator T() const;

    bool isNull() const;
    bool isBool() const;
    bool isNumber() const;
    bool isInt() const;
    bool isUint() const;
    bool isFloat() const;
    bool isString() const;
    bool isList() const;
    bool isMap() const;

    usize size() const;

    bool contains(const string& key) const;
    SerialNode& at(const string& key);
    const SerialNode& at(const string& key) const;
    SerialNode& operator[](const string& key);
    Map<string, SerialNode>& items();
    const Map<string, SerialNode>& items() const;

    SerialNode& at(usize index);
    const SerialNode& at(usize index) const;
    SerialNode& operator[](usize index);
    const SerialNode& operator[](usize index) const;
    List<SerialNode>::iterator begin();
    List<SerialNode>::const_iterator begin() const;
    List<SerialNode>::iterator end();
    List<SerialNode>::const_iterator end() const;

    bool operator==(strview str) const;
    std::partial_ordering operator<=>(const SerialNode& other) const;
    friend ostream& operator<<(ostream& stream, const SerialNode& node);
  private:
    Variant<SerialMap, SerialList, SerialLeaf> _value = SerialLeaf(null());
  };
}
#include "serial_node_impl.hh"