#pragma once
#include "client.hh"

namespace Parrot {
	// Sun
	class Sun : public EntityScript {
	public:
		// Sun
		Sun(Entity& entity)
			: EntityScript(entity) {}

		// onUpdate
		virtual void onUpdate(float32 delta_time) override {
			Vec3<float32> rotation = { 0.0F, 0.5F * delta_time, 0.0F };
			entity->transform.position = calcRotationMatrix(rotation) * Vec4<float32>(entity->transform.position);
		}
	};
}