#include "common.hh"
#include "uuid.hh"
#include "debug/debug.hh"
#include <random>
#include <nlohmann/json.hh>
using json = nlohmann::json;

namespace Parrot {
	// (static)
	static std::random_device s_random;
	static std::uniform_int_distribution<uint64> s_dist;

	// generateUUID
	uuid generateUUID() {
		std::mt19937 rng(s_random());
		return s_dist(rng);
	}

	// UUIDObject
	UUIDObject::UUIDObject()
		: _uuid(generateUUID()) {}
	UUIDObject::UUIDObject(uuid uuid)
		: _uuid(uuid) {}
	UUIDObject::UUIDObject(const stdf::path& filepath)
		: _uuid(0) {
		if (filepath.string().ends_with(".json")) {
			auto data = json::parse(ifstream(filepath));
			if (data.contains("uuid")) {
				_uuid = data.at("uuid");
			}
			else {
				LOG_ASSET_ERROR("asset file {} does not have a 'uuid' property", filepath);
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
	// =
	UUIDObject& UUIDObject::operator=([[maybe_unused]] const UUIDObject& other) {
		_uuid = generateUUID();
		return *this;
	}
	UUIDObject& UUIDObject::operator=(UUIDObject&& other) noexcept {
		_uuid = std::exchange(other._uuid, 0);
		return *this;
	}
	// getUUID
	uuid UUIDObject::getUUID() const {
		return _uuid;
	}
}