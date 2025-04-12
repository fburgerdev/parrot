#pragma once

namespace Parrot {
  template<class T>
  T SerialNode::value() const {
    if (holds<SerialLeaf>(_value)) {
      auto& leaf = std::get<SerialLeaf>(_value);
      if (holds<null>(std::get<SerialLeaf>(_value))) {
        if constexpr (std::is_convertible_v<null, T>) {
          return static_cast<T>(std::get<null>(leaf));
        }
      }
      else if (holds<bool>(std::get<SerialLeaf>(_value))) {
        if constexpr (std::is_convertible_v<bool, T>) {
          return static_cast<T>(std::get<bool>(leaf));
        }
      }
      else if (holds<int64>(std::get<SerialLeaf>(_value))) {
        if constexpr (std::is_convertible_v<int64, T>) {
          return static_cast<T>(std::get<int64>(leaf));
        }
      }
      else if (holds<uint64>(std::get<SerialLeaf>(_value))) {
        if constexpr (std::is_convertible_v<uint64, T>) {
          return static_cast<T>(std::get<uint64>(leaf));
        }
      }
      else if (holds<double>(std::get<SerialLeaf>(_value))) {
        if constexpr (std::is_convertible_v<double, T>) {
          return static_cast<T>((std::get<double>(leaf)));
        }
      }
      else if (holds<string>(std::get<SerialLeaf>(_value))) {
        if constexpr (std::is_convertible_v<string, T>) {
          return static_cast<T>(std::get<string>(leaf));
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

  template<class T>
  SerialNode::operator T() const {
    return value<T>();
  }
}