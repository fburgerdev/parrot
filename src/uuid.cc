#include "common.hh"
#include "uuid.hh"
#include <random>
#include "nlohmann/json.hh"
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
	UUIDObject::UUIDObject(const stdf::path& asset_path)
		: _uuid(0) {
		if (asset_path.string().ends_with(".json")) {
			auto data = json::parse(ifstream(asset_path));
			if (data.contains("uuid")) {
				_uuid = data.at("uuid");
			}
			else {
				// TODO: error
			}
		}
		else {
			// TODO: error
		}
	}
	UUIDObject::UUIDObject([[maybe_unused]] const UUIDObject& other)
		: _uuid(generateUUID()) {}
	UUIDObject::UUIDObject(UUIDObject&& other) noexcept
		: _uuid(std::exchange(other._uuid, 0)) {}
	// getUUID
	uuid UUIDObject::getUUID() const {
		return _uuid;
	}
}