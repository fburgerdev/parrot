#pragma once
#include "common.hh"

namespace Parrot {
  /// @brief Universally-Unique-Identifier, i.e. random generated numbers so
  /// large they can't possibly match with another one by accident.
  using UUID = uint64;
  /// @brief Randomly generate a UUID.
  UUID generateUUID();

  /// @brief Base class for classes that hold a UUID value.
  class UUIDObject {
  public:
    /// @brief Construct a UUIDObject with a randomly generated UUID.
    UUIDObject();
    /// @brief Construct a UUIDObject with a given UUID.
    UUIDObject(UUID uuid);
    /// @deprecated
    UUIDObject(const stdf::path& filepath);
    /// @brief Construct a UUIDObject with a randomly generated UUID.
    /// @note The other UUIDObject is not used, that is because two UUIDObjects
    /// shall never have the same UUID.
    UUIDObject(const UUIDObject& other);
    /// @brief Construct a UUIDObject with the UUID of another UUIDObject.
    /// @note The other UUIDObjects UUID is resetted to 0
    UUIDObject(UUIDObject&& other) noexcept;
    /// @brief Assign a UUIDObject with a randomly generated UUID.
    /// @note The other UUIDObject is not used, that is because two UUIDObjects
    /// shall never have the same UUID.
    UUIDObject& operator=(const UUIDObject& other);
    /// @brief Assign a UUIDObject with the UUID of another UUIDObject.
    /// @note The other UUIDObjects UUID is resetted to 0
    UUIDObject& operator=(UUIDObject&& other) noexcept;

    /// @brief Access the UUID.
    UUID getUUID() const;
  private:
    UUID _uuid;
  };
}