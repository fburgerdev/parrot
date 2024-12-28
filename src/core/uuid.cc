#include "common.hh"
#include "core/uuid.hh"
#include "debug/engine_logger.hh"
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
		: _id(generateUUID()) {}
	UUIDObject::UUIDObject(uuid id)
		: _id(id) {}
	UUIDObject::UUIDObject(const stdf::path& filepath)
		: _id(0) {
		if (filepath.string().ends_with(".json")) {
			auto data = json::parse(ifstream(filepath));
			if (data.contains("uuid")) {
				_id = data.at("uuid");
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
		: _id(generateUUID()) {}
	UUIDObject::UUIDObject(UUIDObject&& other) noexcept
		: _id(std::exchange(other._id, 0)) {}
	// =
	UUIDObject& UUIDObject::operator=([[maybe_unused]] const UUIDObject& other) {
		_id = generateUUID();
		return *this;
	}
	UUIDObject& UUIDObject::operator=(UUIDObject&& other) noexcept {
		_id = std::exchange(other._id, 0);
		return *this;
	}
	// getUUID
	uuid UUIDObject::getUUID() const {
		return _id;
	}
}