#include "Physics.h"

namespace physics {
	Vec2 CalculateVelocity(Vec2 currentPos, Vec2 targetPos, float constantVelocity) {
		if (currentPos != targetPos) {
			// Calculate the displacement vector from current position to target position
			Vec2 displacement = { targetPos.x - currentPos.x, targetPos.y - currentPos.y };

			// Calculate the distance between current position and target position
			float distance = std::sqrt(displacement.x * displacement.x + displacement.y * displacement.y);

			// Calculate the unit vector of the displacement
			Vec2 unitVector = { displacement.x / distance, displacement.y / distance };

			// Calculate the velocity vector with the given constant magnitude
			Vec2 velocity = { constantVelocity * unitVector.x, constantVelocity * unitVector.y };

			return velocity;
		}
		else {
			return Vec2(1, 1);
		}
	}
}