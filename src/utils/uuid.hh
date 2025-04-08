#pragma once
#include "common.hh"

namespace Parrot {
  using UUID = uint64;
  UUID generateUUID();

  class UUIDObject {
  public:
    UUIDObject();
    UUIDObject(UUID uuid);
    UUIDObject(const stdf::path& filepath);
    UUIDObject(const UUIDObject& other);
    UUIDObject(UUIDObject&& other) noexcept;
    UUIDObject& operator=(const UUIDObject& other);
    UUIDObject& operator=(UUIDObject&& other) noexcept;

    UUID getUUID() const;
  private:
    UUID _uuid;
  };
}