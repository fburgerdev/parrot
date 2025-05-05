#pragma once
#include "serial_path.hh"

namespace Parrot {
  template<class T, class... Args>
  concept Deserializable = requires(Args&&... args) {
    { fromSerialNode<T>(args...) } -> std::same_as<Opt<T>>;
  } || std::is_convertible_v<string, T>;

  struct StructureNode {
    using StructureMap = Map<strview, StructureNode>;
    using StructureList = List<StructureNode>;
    using StructureLeaf = Func<void(const SerialNode&, const SerialPath&)>;

    template<class T, class... Args>
      requires Deserializable<T, SerialNode, SerialPath, Args...>
    StructureNode(T& target, Args&&... args)
      : _value([&](const SerialNode& node, const SerialPath& path) {
        if constexpr (std::is_convertible_v<string, T>) {
          target = string(node);
        }
        else {
          auto x = fromSerialNode<T>(node, path, std::forward<Args>(args)...);
          if (x.has_value()) {
            target = x.value();
          }
          else {
            throw;
          }
        }
      }) {}
    StructureNode(StructureMap&& map)
      : _value(std::move(map)) {}
    StructureNode(StructureList&& list)
      : _value(std::move(list)) {}

    bool isMap() const {
      return holds<StructureMap>(_value);
    }
    bool isList() const {
      return holds<StructureList>(_value);
    }
    bool isLeaf() const {
      return holds<StructureLeaf>(_value);
    }

    StructureMap& asMap() {
      return std::get<StructureMap>(_value);
    }
    StructureList& asList() {
      return std::get<StructureList>(_value);
    }
    StructureLeaf& asLeaf() {
      return std::get<StructureLeaf>(_value);
    }
  private:
    Variant<StructureMap, StructureList, StructureLeaf> _value;
  };

  class Deserializer {
  public:
    enum class ErrorPolicy {
      INSTANT_ERROR, TRY_FALLBACK,
    };

    template<class T, class... Args>
    void deserialize(const stdf::path& path, T& target, Args&&... args) {
      _path = SerialPath{path};
      auto structure = target.structure(std::forward<Args>(args)...);
      deserialize(SerialNode::loadFromJSON(path), structure);
    }
    void load(const stdf::path& path, StructureNode& structure) {
      _path = SerialPath{ path };
      deserialize(SerialNode::loadFromJSON(path), structure);
    }

    ErrorPolicy getErrorPolicy() {
      return _error_policy;
    }
    void setErrorPolicy(ErrorPolicy error_policy) {
      _error_policy = error_policy;
    }
  private:
    void deserialize(const SerialNode& serial, StructureNode& structure) {
      if (structure.isMap()) {
        if (serial.isMap()) {
          for (auto& [key, value] : structure.asMap()) {
            string old_sub = _path.sub;
            _path.sub += '.';
            _path.sub += key;
            deserialize(serial.at(string(key)), value);
            _path.sub = old_sub;
          }
        }
      }
      else if (structure.isList()) {
        if (serial.isList()) {
          for (usize i = 0; i < structure.asList().size(); ++i) {
            string old_sub = _path.sub;
            _path.sub += '[';
            _path.sub += std::to_string(i);
            _path.sub += ']';
            deserialize(serial.at(i), structure.asList().at(i));
            _path.sub = old_sub;
          }
        }
      }
      else if (structure.isLeaf()) {
        structure.asLeaf()(serial, _path);
      }
    }

    ErrorPolicy _error_policy = ErrorPolicy::INSTANT_ERROR;
    SerialPath _path;
  };
}