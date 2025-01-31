#include "common.hh"
#include "core/uuid.hh"
#include "debug/engine_logger.hh"
#include <random>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Parrot {
  // (static)
  static std::random_device s_random;
  static std::uniform_int_distribution<uint64> s_dist;

  // generateUUID
  UUID generateUUID() {
    std::mt19937 rng(s_random());
    return s_dist(rng);
  }

  // (constructor)
  UUIDObject::UUIDObject()
    : _uuid(generateUUID()) {}
  UUIDObject::UUIDObject(UUID uuid)
    : _uuid(uuid) {}
  UUIDObject::UUIDObject(const stdf::path& filepath)
    : _uuid(0) {
    if (filepath.string().ends_with(".json")) {
      auto data = json::parse(ifstream(filepath));
      if (data.contains("uuid")) {
        _uuid = data.at("uuid");
      }
      else {
        LOG_ASSET_ERROR(
          "asset file {} does not have a 'uuid' property", filepath
        );
      }
    }
    else {
      LOG_ASSET_ERROR("unsupported asset file extension in {}", filepath);
    }
  }
  UUIDObject::UUIDObject([[maybe_unused]] const UUIDObject& other)
    : _uuid(generateUUID()) {}
  UUIDObject::UUIDObject(UUIDObject&& other) noexcept
    : _uuid(std::exchange(other._uuid, 0)) {}
  // (assignment)
  UUIDObject& UUIDObject::operator=([[maybe_unused]] const UUIDObject& other) {
    _uuid = generateUUID();
    return *this;
  }
  UUIDObject& UUIDObject::operator=(UUIDObject&& other) noexcept {
    _uuid = std::exchange(other._uuid, 0);
    return *this;
  }
  // getUUID
  UUID UUIDObject::getUUID() const {
    return _uuid;
  }
}